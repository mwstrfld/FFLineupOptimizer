#include <QCompleter>
#include <QDebug>
#include <QString>
#include <QFileDialog>
#include <QStandardItemModel>

#include <AddPlayerDialog.h>
#include <CsvParser.h>
#include <LineupOptimizerFrontEnd.h>
#include <ui_LineupOptimizerFrontEnd.h>


LineupOptimizerFrontEnd::LineupOptimizerFrontEnd( QWidget* parent )
    : QMainWindow( parent ),
      m_ui( new Ui::FFLineupOptimizerFrontEnd )
{
    // Parent the actual UI
    m_ui->setupUi( this );

    // Create a new CSV Parser
    m_parser = new CsvParser();

    // Create new models for rankings displays
    // Overall
    m_overallRankingsModel = new QStandardItemModel( this );
    m_ui->overallRankingsTableView->setModel( m_overallRankingsModel );
    // QB
    m_qbRankingsModel = new QStandardItemModel( this );
    m_ui->qbRankingsTableView->setModel( m_qbRankingsModel );
    // WR
    m_wrRankingsModel = new QStandardItemModel( this );
    m_ui->wrRankingsTableView->setModel( m_wrRankingsModel );
    // RB
    m_rbRankingsModel = new QStandardItemModel( this );
    m_ui->rbRankingsTableView->setModel( m_rbRankingsModel );
    // TE
    m_teRankingsModel = new QStandardItemModel( this );
    m_ui->teRankingsTableView->setModel( m_teRankingsModel );
    // K
    m_kRankingsModel = new QStandardItemModel( this );
    m_ui->kRankingsTableView->setModel( m_kRankingsModel );
    // DST
    m_dstRankingsModel = new QStandardItemModel( this );
    m_ui->dstRankingsTableView->setModel( m_dstRankingsModel );

    // Signal/slot connections
    connect( m_ui->selectRankingsButton, SIGNAL( pressed() ), SLOT( handleSelectRankingsButtonPressed() ) );
    connect( m_ui->addPlayerButton, SIGNAL( pressed() ), SLOT( handleAddPlayerButtonPressed() ) );

    // Initialize My Team
    initializeMyTeamModel();
}


LineupOptimizerFrontEnd::~LineupOptimizerFrontEnd()
{
    delete m_ui;
}



QStandardItemModel* LineupOptimizerFrontEnd::getPositionModel( Player::Position pos )
{
    QStandardItemModel* retModel = 0;

    switch( pos )
    {
    case Player::Position::QB:
        retModel = m_qbRankingsModel;
        break;
    case Player::Position::WR:
        retModel = m_wrRankingsModel;
        break;
    case Player::Position::RB:
        retModel = m_rbRankingsModel;
        break;
    case Player::Position::TE:
        retModel = m_teRankingsModel;
        break;
    case Player::Position::K:
        retModel = m_qbRankingsModel;
        break;
    case Player::Position::DST:
        retModel = m_dstRankingsModel;
        break;
    default:
        break;
    }

    return retModel;
}


bool LineupOptimizerFrontEnd::addPlayerToTeam( Player::Position pos, const QString& name )
{
    bool retVal = false;

    // TODO - Fix this hardcoded number later
    if( m_myTeam.size() < 15 )
    {
        auto rankings = getRankingsForPosition( pos );
        for( auto itr = rankings.begin(); itr != rankings.end(); ++itr )
        {
            // If name exists in rankings
            if( !QString::compare( (*itr).getName(), name, Qt::CaseInsensitive ) )
            {
                auto findItr = std::find_if( m_myTeam.begin(),
                                             m_myTeam.end(),
                                             [&pos, &name](const Player& p)
                {
                    // If name/pos combo already exists on team
                    return (p.getPosition() == pos) &&
                           !QString::compare( p.getName(), name, Qt::CaseInsensitive );
                });

                // Name exists in rankings and not already on team
                if( findItr == m_myTeam.end() )
                {
                    m_myTeam.push_back( *itr );
                    retVal = true;
                    break;
                }
            }
        }
    }

    updateMyTeamDisplay();

    return retVal;
}


std::vector< Player >& LineupOptimizerFrontEnd::getRankingsForPosition( Player::Position pos )
{
    return m_parser->getRankingsForPosition( pos );
}


void LineupOptimizerFrontEnd::handleSelectRankingsButtonPressed()
{
    Player::Position pos = Player::Position::NONE;
    QStandardItemModel* model = 0;

    QString windowTitle = "Open ";

    auto ind = m_ui->rankingsTabWidget->currentIndex();
    switch( ind )
    {
    case 0: // Overall
        windowTitle.append( "Overall" );
        pos = Player::Position::NONE;
        model = m_overallRankingsModel;
        break;
    case 1: // QB
        windowTitle.append( "Quarterback" );
        pos = Player::Position::QB;
        model = m_qbRankingsModel;
        break;
    case 2: // WR
        windowTitle.append( "Wide Receiver" );
        pos = Player::Position::WR;
        model = m_wrRankingsModel;
        break;
    case 3: // RB
        windowTitle.append( "Running Back" );
        pos = Player::Position::RB;
        model = m_rbRankingsModel;
        break;
    case 4: // TE
        windowTitle.append( "Tight End" );
        pos = Player::Position::TE;
        model = m_teRankingsModel;
        break;
    case 5: // K
        windowTitle.append( "Kicker" );
        pos = Player::Position::K;
        model = m_kRankingsModel;
        break;
    case 6: // DEF
        windowTitle.append( "Defense/Special Teams" );
        pos = Player::Position::DST;
        model = m_dstRankingsModel;
        break;
    default:
        break;
    }

    windowTitle.append( " Rankings CSV File" );
    QString fileName = QFileDialog::getOpenFileName( this,
                                                     windowTitle,
                                                     QDir::currentPath(),
                                                     "CSV (*.csv)" );

    model->clear();
    m_parser->parseRankings( pos, fileName, model );
}


void LineupOptimizerFrontEnd::handleAddPlayerButtonPressed()
{
    auto apd = new AddPlayerDialog( this );
    apd->show();
}


void LineupOptimizerFrontEnd::initializeMyTeamModel()
{
    // Create the model for the team display
    m_myTeamModel = new QStandardItemModel( this );
    m_ui->myTeamTableView->setModel( m_myTeamModel );

    // Set the horizontal header labels
    QStringList hHeaders = { "Player", "Overall Ranking", "Position Ranking" };
    m_myTeamModel->setHorizontalHeaderLabels( hHeaders );

    // Set the vertical header labels
    QStringList vHeaders = { "QB", "WR1", "WR2", "WR3", "RB1", "RB2", "TE", "K", "DEF",
                             "BEN1", "BEN2", "BEN3", "BEN4", "BEN5", "BEN6" };
    m_myTeamModel->setVerticalHeaderLabels( vHeaders );
}


void LineupOptimizerFrontEnd::updateMyTeamDisplay()
{

}
