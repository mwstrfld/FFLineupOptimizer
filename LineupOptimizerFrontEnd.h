#pragma once


#include <QMainWindow>


// Forward declarations
class CsvParser;
class QStandardItemModel;

namespace Ui
{
    class FFLineupOptimizerFrontEnd;
}


class LineupOptimizerFrontEnd : public QMainWindow
{
    Q_OBJECT

public:
    LineupOptimizerFrontEnd( QWidget* parent = 0 );
    ~LineupOptimizerFrontEnd();

protected slots:
    void handleOptimizeButtonPressed();

protected:
    // Actual UI
    Ui::FFLineupOptimizerFrontEnd *m_ui;

    // CSV Parser
    CsvParser* m_parser;

    // Rankings model
    QStandardItemModel* m_rankingsModel;
};
