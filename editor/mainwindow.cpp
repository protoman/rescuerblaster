#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    dataloading = true;
    Mediator::get_instance()->load();

    ui->setupUi(this);

    fill_stage_combo();
    fill_map_combo();

    set_stage_data();
    set_map_data();

    dataloading = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Rockbot Editor :: Game Editor", tr("Save data before leaving?\n"), QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes);
    if (resBtn == QMessageBox::Yes) {
        Mediator::get_instance()->save();
    } else if (resBtn == QMessageBox::Cancel) {
        event->ignore();
        return;
    }
    event->accept();
}

void MainWindow::on_addMap_pushButton_clicked()
{
    Mediator::get_instance()->map_list_map.at(Mediator::get_instance()->currentStage).push_back(st_file_map());
    Mediator::get_instance()->save();
    fill_map_combo();
}


void MainWindow::on_addStage_pushButton_clicked()
{
    Mediator::get_instance()->stage_list.push_back(st_file_stage());
    Mediator::get_instance()->save();
    fill_stage_combo();
    fill_map_combo();
}

void MainWindow::fill_exists_combo(QComboBox *combo)
{
    combo->clear();
    combo->addItem("");
    for (unsigned int i=0; i<Mediator::get_instance()->map_list_map.at(Mediator::get_instance()->currentStage).size(); i++) {
        combo->addItem(QString::number(i));
    }
}

void MainWindow::on_actionSave_triggered()
{
    Mediator::get_instance()->save();
}

void MainWindow::on_actionLoad_triggered()
{

}

void MainWindow::on_currentStage_comboBox_currentIndexChanged(int index)
{
    if (dataloading) { return; }
    Mediator::get_instance()->save();
    Mediator::get_instance()->currentStage = index;
    Mediator::get_instance()->currentMap = 0;
    ui->editArea->repaint();
}

void MainWindow::on_currentMap_comboBox_currentIndexChanged(int index)
{
    if (dataloading) { return; }
    Mediator::get_instance()->save();
    Mediator::get_instance()->currentMap = index;
    dataloading = true;

    fill_exists_map_combo();
    set_map_data();

    dataloading = false;
    ui->editArea->repaint();
}

void MainWindow::fill_stage_combo()
{
    ui->currentStage_comboBox->clear();
    for (int i=0; i<Mediator::get_instance()->stage_list.size(); i++) {
        ui->currentStage_comboBox->addItem(QString::number(i));
    }
}

void MainWindow::fill_map_combo()
{
    ui->currentMap_comboBox->clear();
    for (int i=0; i<Mediator::get_instance()->map_list_map.at(Mediator::get_instance()->currentStage).size(); i++) {
        ui->currentMap_comboBox->addItem(QString::number(i));
    }
    fill_exists_map_combo();
}

void MainWindow::fill_exists_map_combo()
{
    fill_exists_combo(ui->north_comboBox);
    fill_exists_combo(ui->south_comboBox);
    fill_exists_combo(ui->west_comboBox);
    fill_exists_combo(ui->east_comboBox);
}


void MainWindow::set_stage_data()
{
}

void MainWindow::set_map_data()
{
    st_file_map* map = &Mediator::get_instance()->map_list_map.at(Mediator::get_instance()->currentStage).at(Mediator::get_instance()->currentMap);

    ui->north_comboBox->setCurrentIndex(map->north+1);
    ui->south_comboBox->setCurrentIndex(map->south+1);
    ui->west_comboBox->setCurrentIndex(map->west+1);
    ui->east_comboBox->setCurrentIndex(map->east+1);

}

void MainWindow::on_north_comboBox_currentIndexChanged(int index)
{
    if (dataloading) { return; }

    std::cout << "on_north_comboBox_currentIndexChanged" << std::endl;
    st_file_map* map = &Mediator::get_instance()->map_list_map.at(Mediator::get_instance()->currentStage).at(Mediator::get_instance()->currentMap);
    if (map->south == index) {
        map->south = -1;
    }
    if (map->west == index) {
        map->west = -1;
    }
    if (map->east == index) {
        map->east = -1;
    }
    int old_north = map->north;
    map->north = index-1;
    if (map->north != -1) {
        Mediator::get_instance()->map_list_map.at(Mediator::get_instance()->currentStage).at(map->north).south = Mediator::get_instance()->currentMap;
        std::cout << "SET SOUTH on map[" << map->north << "], SET[" << Mediator::get_instance()->map_list_map.at(Mediator::get_instance()->currentStage).at(map->north).south << "]" << std::endl;
    }
    if (old_north != -1) {
        std::cout << "RESET-OLD-SOUTH[" << old_north << "]" << std::endl;
        Mediator::get_instance()->map_list_map.at(Mediator::get_instance()->currentStage).at(old_north).south = -1;
    }
    Mediator::get_instance()->save();
}


void MainWindow::on_south_comboBox_currentIndexChanged(int index)
{
    if (dataloading) { return; }
    std::cout << "on_south_comboBox_currentIndexChanged" << std::endl;
    st_file_map* map = &Mediator::get_instance()->map_list_map.at(Mediator::get_instance()->currentStage).at(Mediator::get_instance()->currentMap);
    if (map->north == index) {
        map->north = -1;
    }
    if (map->west == index) {
        map->west = -1;
    }
    if (map->east == index) {
        map->east = -1;
    }
    int old_south = map->south;
    map->south = index-1;
    if (map->south != -1) {
        Mediator::get_instance()->map_list_map.at(Mediator::get_instance()->currentStage).at(map->south).north = Mediator::get_instance()->currentMap;
    }
    if (old_south != -1) {
        Mediator::get_instance()->map_list_map.at(Mediator::get_instance()->currentStage).at(old_south).north = -1;
    }
    Mediator::get_instance()->save();
}
