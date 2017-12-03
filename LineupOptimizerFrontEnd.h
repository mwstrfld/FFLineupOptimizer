#pragma once


#include <QMainWindow>

#include <CsvParser.h>


// Forward declarations
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
    void handleSelectRankingsButtonPressed();

protected:
    // Actual UI
    Ui::FFLineupOptimizerFrontEnd *m_ui;

    // CSV Parser
    CsvParser* m_parser;

    // Helper function for My Team model initialization
    void initializeMyTeamModel();

    // My Team model
    QStandardItemModel* m_myTeamModel;

    // Rankings models
    QStandardItemModel* m_overallRankingsModel;
    QStandardItemModel* m_qbRankingsModel;
    QStandardItemModel* m_wrRankingsModel;
    QStandardItemModel* m_rbRankingsModel;
    QStandardItemModel* m_teRankingsModel;
    QStandardItemModel* m_kRankingsModel;
    QStandardItemModel* m_dstRankingsModel;
};
