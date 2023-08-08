#ifndef SIMULATIONWINDOW_H
#define SIMULATIONWINDOW_H

#include "src/management/packagetablemodel.h"
#include "src/management/simulationmanager.h"
#include <QMainWindow>
#include <QKeyEvent>
#include <QTreeWidget>

namespace Ui {
class SimulationWindow;
}

class SimulationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SimulationWindow(SimulationManager* manager, QWidget *parent = nullptr);
    ~SimulationWindow();
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::SimulationWindow* ui;
    SimulationManager* manager;
    PackageTableModel* m_packageModel;
    QTreeWidget* m_treeWidget;
    void setupNetwork();

private slots:
    void openDocumentation();
    void updateTreeWidget(const QModelIndex& index);
    void about();

};

#endif // SIMULATIONWINDOW_H
