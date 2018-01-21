#include <SettingsDialog.h>
#include <ui_SettingsDialog.h>


SettingsDialog::SettingsDialog( QWidget* parent )
    : QDialog( parent ),
      m_ui( new Ui::SettingsDialog ),
      m_qbCount( 0 ),
      m_wrCount( 0 ),
      m_rbCount( 0 ),
      m_teCount( 0 ),
      m_flexCount( 0 ),
      m_kCount( 0 ),
      m_dstCount( 0 ),
      m_benchCount( 0 )
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


// Override Paint Event
void SettingsDialog::paintEvent( QPaintEvent* event )
{
    m_ui->qbLineEdit->setText( QString( "%1" ).arg( m_qbCount ) );
    m_ui->wrLineEdit->setText( QString( "%1" ).arg( m_wrCount ) );
    m_ui->rbLineEdit->setText( QString( "%1" ).arg( m_rbCount ) );
    m_ui->teLineEdit->setText( QString( "%1" ).arg( m_teCount ) );
    m_ui->flexLineEdit->setText( QString( "%1" ).arg( m_flexCount ) );
    m_ui->kLineEdit->setText( QString( "%1" ).arg( m_kCount ) );
    m_ui->dstLineEdit->setText( QString( "%1" ).arg( m_dstCount ) );
    m_ui->benchLineEdit->setText( QString( "%1" ).arg( m_benchCount ) );
}


// Count setters
void SettingsDialog::setQbCount( quint8 count )
{
    m_qbCount = count;
}

void SettingsDialog::setWrCount( quint8 count )
{
    m_wrCount = count;
}

void SettingsDialog::setRbCount( quint8 count )
{
    m_rbCount = count;
}

void SettingsDialog::setTeCount( quint8 count )
{
    m_teCount = count;
}

void SettingsDialog::setFlexCount( quint8 count )
{
    m_flexCount = count;
}

void SettingsDialog::setKCount( quint8 count )
{
    m_kCount = count;
}

void SettingsDialog::setDstCount( quint8 count )
{
    m_dstCount = count;
}

void SettingsDialog::setBenchCount( quint8 count )
{
    m_benchCount = count;
}


// Count getters
quint8 SettingsDialog::getQbCount() const
{
    return m_qbCount;
}

quint8 SettingsDialog::getWrCount() const
{
    return m_wrCount;
}

quint8 SettingsDialog::getRbCount() const
{
    return m_rbCount;
}

quint8 SettingsDialog::getTeCount() const
{
    return m_teCount;
}

quint8 SettingsDialog::getFlexCount() const
{
    return m_flexCount;
}

quint8 SettingsDialog::getKCount() const
{
    return m_kCount;
}

quint8 SettingsDialog::getDstCount() const
{
    return m_dstCount;
}

quint8 SettingsDialog::getBenchCount() const
{
    return m_benchCount;
}


void SettingsDialog::onOkButtonPressed()
{
    // Set the counts
    m_qbCount = static_cast<quint8>( m_ui->qbLineEdit->text().toUInt() );
    m_wrCount = static_cast<quint8>( m_ui->wrLineEdit->text().toUInt() );
    m_rbCount = static_cast<quint8>( m_ui->rbLineEdit->text().toUInt() );
    m_teCount = static_cast<quint8>( m_ui->teLineEdit->text().toUInt() );
    m_flexCount = static_cast<quint8>( m_ui->flexLineEdit->text().toUInt() );
    m_kCount = static_cast<quint8>( m_ui->kLineEdit->text().toUInt() );
    m_dstCount = static_cast<quint8>( m_ui->dstLineEdit->text().toUInt() );
    m_benchCount = static_cast<quint8>( m_ui->benchLineEdit->text().toUInt() );

    // Now close
    hide();
}

void SettingsDialog::onCancelButtonPressed()
{
    // Simply close
    hide();
}
