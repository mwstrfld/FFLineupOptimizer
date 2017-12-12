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

    QStandardItemModel* getPositionModel( Player::Position pos );
    std::vector< Player >& getRankingsForPosition( Player::Position pos );

    bool addPlayerToTeam( Player::Position pos, const QString& name );

protected slots:
    void handleSelectRankingsButtonPressed();
    void handleAddPlayerButtonPressed();

protected:
    // Actual UI
    Ui::FFLineupOptimizerFrontEnd *m_ui;

    // CSV Parser
    CsvParser* m_parser;

    // Helper function for My Team model initialization
    void initializeMyTeamModel();

    // Helper function for updating My Team model
    void updateMyTeamDisplay();

    // My Team model and vector
    QStandardItemModel* m_myTeamModel;
    std::vector< Player > m_myTeam;

    // Rankings models
    QStandardItemModel* m_overallRankingsModel;
    QStandardItemModel* m_qbRankingsModel;
    QStandardItemModel* m_wrRankingsModel;
    QStandardItemModel* m_rbRankingsModel;
    QStandardItemModel* m_teRankingsModel;
    QStandardItemModel* m_kRankingsModel;
    QStandardItemModel* m_dstRankingsModel;
};
