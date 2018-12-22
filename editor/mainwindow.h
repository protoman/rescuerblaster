#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include "mediator.h"
#include "file_map.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void closeEvent(QCloseEvent *event);

private slots:
    void on_addMap_pushButton_clicked();

    void on_actionSave_triggered();

    void on_actionLoad_triggered();

    void on_currentStage_comboBox_currentIndexChanged(int index);

    void on_currentMap_comboBox_currentIndexChanged(int index);

    void fill_stage_combo();
    void fill_map_combo();
    void fill_exists_map_combo();

    void on_addStage_pushButton_clicked();

    void fill_exists_combo(QComboBox* combo);

    void on_north_comboBox_currentIndexChanged(int index);

    void set_stage_data();
    void set_map_data();

    void on_south_comboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    bool dataloading;
};

#endif // MAINWINDOW_H
