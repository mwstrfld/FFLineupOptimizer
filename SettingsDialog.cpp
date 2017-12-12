#include <SettingsDialog.h>
#include <ui_SettingsDialog.h>


SettingsDialog::SettingsDialog( QWidget* parent )
    : QDialog( parent ),
      m_ui( new Ui::SettingsDialog )
{
    // Parent the actual UI
    m_ui->setupUi( this );

    // Signal/slot connections
    connect( m_ui->okButton, SIGNAL( pressed() ), this, SLOT( onOkButtonPressed() ) );
    connect( m_ui->cancelButton, SIGNAL( pressed() ), this, SLOT( onCancelButtonPressed() ) );
}


SettingsDialog::~SettingsDialog()
{
    delete m_ui;
}


void SettingsDialog::onOkButtonPressed()
{
}


void SettingsDialog::onCancelButtonPressed()
{
    // Simply close
    close();
}
