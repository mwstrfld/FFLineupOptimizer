#pragma once


#include <QDialog>

#include <Player.h>


// Forward declarations
class LineupOptimizerFrontEnd;

namespace Ui
{
    class AddPlayerDialog;
}


class AddPlayerDialog : public QDialog
{
    Q_OBJECT

public:
    AddPlayerDialog( QWidget* parent = 0 );
    ~AddPlayerDialog();

protected slots:
    void onSubmitButtonPressed();
    void onCloseButtonPressed();
    void handlePositionChange( int );

protected:
    // Actual UI
    Ui::AddPlayerDialog* m_ui;

    // Current player position selection
    Player::Position m_currentPosition;

    // Own reference to the LineupOptimizerFrontEnd
    LineupOptimizerFrontEnd* m_frontEnd;
};
