#include "editorarea.h"

const int line_w_n = SCREEN_WIDTH/TILESIZE;
const int line_h_n = VISIBLE_HEIGHT/TILESIZE;

editorArea::editorArea(QWidget *parent) : QWidget(parent)
{
    myParent = parent;
    zoom = 0.5;
}

void editorArea::mousePressEvent(QMouseEvent *event)
{
    QPoint pnt = event->pos();
    editor_selectedTileX = pnt.x()/(TILESIZE*zoom);
    editor_selectedTileY = pnt.y()/(TILESIZE*zoom);

    if (Mediator::get_instance()->map_list_map.at(Mediator::get_instance()->currentStage).size() == 0) {
        Mediator::get_instance()->map_list_map.at(Mediator::get_instance()->currentStage).push_back(st_file_map());
    }
    // TODO: check size against selected

    int currentTileValue = Mediator::get_instance()->map_list_map.at(Mediator::get_instance()->currentStage).at(Mediator::get_instance()->currentMap).tile[editor_selectedTileX][editor_selectedTileY];
    Mediator::get_instance()->map_list_map.at(Mediator::get_instance()->currentStage).at(Mediator::get_instance()->currentMap).tile[editor_selectedTileX][editor_selectedTileY]++;
    if (Mediator::get_instance()->map_list_map.at(Mediator::get_instance()->currentStage).at(Mediator::get_instance()->currentMap).tile[editor_selectedTileX][editor_selectedTileY] > 2) {
        Mediator::get_instance()->map_list_map.at(Mediator::get_instance()->currentStage).at(Mediator::get_instance()->currentMap).tile[editor_selectedTileX][editor_selectedTileY] = 0;
    }
    repaint();
}

void editorArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QLineF line;

    if (Mediator::get_instance()->map_list_map.at(Mediator::get_instance()->currentStage).size() == 0 || Mediator::get_instance()->map_list_map.at(Mediator::get_instance()->currentStage).size() <= Mediator::get_instance()->currentMap) {
        return;
    }

    //std::cout << "VISIBLE_HEIGHT[" << VISIBLE_HEIGHT << "], MAP_H[" << MAP_H << "]" << std::endl;

    // DRAW TILES //
    for (int i=0; i<MAP_W; i++) {
        for (int j=0; j<MAP_H; j++) {
            int currentTileValue = Mediator::get_instance()->map_list_map.at(Mediator::get_instance()->currentStage).at(Mediator::get_instance()->currentMap).tile[i][j];
            st_file_color color;
            if (currentTileValue == 1) {
                color = st_file_color(0, 100, 0);
            } else if (currentTileValue == 2) {
                color = st_file_color(100, 0, 0);
            } else {
                color = st_file_color(0, 0, 0);
                // TODO: use stage color
                //color = Mediator::get_instance()->map_list_map.at(Mediator::get_instance()->currentStage).at(currentMap).map_color[STAGE_COLOR_BACKGROUND];
            }
            painter.fillRect(QRectF(i*TILESIZE*zoom, j*TILESIZE*zoom, TILESIZE*zoom, TILESIZE*zoom), QColor(color.r, color.g, color.b, 255));
        }
    }

    // DRAW GRID //
    QPen pen(QColor(160, 160, 160), 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen_red(QColor(180, 50, 50), 2, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);
    for (int i=0; i<=line_w_n; i++) {
        int pos = i*TILESIZE*zoom;
        // linhas verticais
        line = QLineF(pos, 0, pos, VISIBLE_HEIGHT*zoom);
        if (i == 0 || i % 20 == 0) {
            painter.setPen(pen_red);
        } else {
            painter.setPen(pen);
        }
        painter.drawLine(line);
    }
    painter.setPen(pen);
    for (int i=0; i<=line_h_n; i++) {
        int pos = i*TILESIZE*zoom;
        // linhas horizontais
        line = QLineF(0, pos, SCREEN_WIDTH*zoom, pos);
        if (i == 0 || i == VISIBLE_HEIGHT/TILESIZE) {
            painter.setPen(pen_red);
        } else {
            painter.setPen(pen);
        }
        painter.drawLine(line);
    }

    QSize resizeMe(SCREEN_WIDTH*zoom, VISIBLE_HEIGHT*zoom);
    this->resize(resizeMe);
    myParent->adjustSize();


}
