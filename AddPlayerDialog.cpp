#include <AddPlayerDialog.h>
#include <LineupOptimizerFrontEnd.h>
#include <ui_AddPlayerDialog.h>

#include <QCompleter>
#include <QStandardItemModel>
#include <QMessageBox>


AddPlayerDialog::AddPlayerDialog( QWidget* parent )
    : QDialog( parent ),
      m_ui( new Ui::AddPlayerDialog ),
      m_frontEnd( 0 ),
      m_currentPosition( Player::Position::NONE )
{
    // Parent the actual UI
    m_ui->setupUi( this );

    // Set modal
    setModal( true );

    m_frontEnd = dynamic_cast< LineupOptimizerFrontEnd* >( parent );

    // Setup the completer for QB
    handlePositionChange( 0 );

    // Signal/slot connections
    connect( m_ui->submitButton, SIGNAL( pressed() ), this, SLOT( onSubmitButtonPressed() ) );
    connect( m_ui->closeButton, SIGNAL( pressed() ), this, SLOT( onCloseButtonPressed() ) );
    connect( m_ui->positionComboBox, SIGNAL( currentIndexChanged( int ) ), this, SLOT( handlePositionChange( int ) ) );
}


AddPlayerDialog::~AddPlayerDialog()
{
    delete m_ui;
}


void AddPlayerDialog::onSubmitButtonPressed()
{
    if( m_frontEnd->addPlayerToTeam( m_currentPosition, m_ui->playerLineEdit->text() ) )
    {
        // Close the dialog
        close();
    }
    else
    {
        // Unsuccessful
        QString errorMsg = "Could not add player for one of the following reasons:\n";
        errorMsg += "1. Your team is full\n";
        errorMsg += "2. The entered player is already on your team\n";
        errorMsg += "3. The entered player name did not match any names in the rankings";
        QMessageBox::question( this,
                               "Cannot Add Player",
                               errorMsg,
                               QMessageBox::Ok );
    }
}


void AddPlayerDialog::onCloseButtonPressed()
{
    // Simply close
    close();
}


void AddPlayerDialog::handlePositionChange( int pos )
{
    std::vector< Player >& positionVector = m_frontEnd->getRankingsForPosition( Player::Position::NONE );

    switch( pos )
    {
    case 0: // QB
        m_currentPosition = Player::Position::QB;
        positionVector = m_frontEnd->getRankingsForPosition( Player::Position::QB );
        break;
    case 1: // WR
        m_currentPosition = Player::Position::WR;
        positionVector = m_frontEnd->getRankingsForPosition( Player::Position::WR );
        break;
    case 2: // RB
        m_currentPosition = Player::Position::RB;
        positionVector = m_frontEnd->getRankingsForPosition( Player::Position::RB );
        break;
    case 3: // TE
        m_currentPosition = Player::Position::TE;
        positionVector = m_frontEnd->getRankingsForPosition( Player::Position::TE );
        break;
    case 4: // K
        m_currentPosition = Player::Position::K;
        positionVector = m_frontEnd->getRankingsForPosition( Player::Position::K );
        break;
    case 5: // D/ST
        m_currentPosition = Player::Position::DST;
        positionVector = m_frontEnd->getRankingsForPosition( Player::Position::DST );
        break;
    default:
        break;
    }

    if( !positionVector.empty() )
    {
        QStringList playerNames;
        for( auto itr = positionVector.begin(); itr != positionVector.end(); ++itr )
            playerNames.append( (*itr).getName() );

        auto completer = new QCompleter( playerNames, this );
        m_ui->playerLineEdit->setCompleter( completer );
    }
}
