#pragma once


#include <QDialog>


// Forward declarations
namespace Ui
{
    class SettingsDialog;
}


class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    SettingsDialog( QWidget* parent = 0 );
    ~SettingsDialog();

    // Count setters
    void setQbCount( quint8 count );
    void setWrCount( quint8 count );
    void setRbCount( quint8 count );
    void setTeCount( quint8 count );
    void setFlexCount( quint8 count );
    void setKCount( quint8 count );
    void setDstCount( quint8 count );
    void setBenchCount( quint8 count );

    // Count getters
    quint8 getQbCount() const;
    quint8 getWrCount() const;
    quint8 getRbCount() const;
    quint8 getTeCount() const;
    quint8 getFlexCount() const;
    quint8 getKCount() const;
    quint8 getDstCount() const;
    quint8 getBenchCount() const;

protected slots:
    void onOkButtonPressed();
    void onCancelButtonPressed();

protected:
    // Actual UI
    Ui::SettingsDialog* m_ui;

    // Override Paint Event
    virtual void paintEvent( QPaintEvent* event );

    // Counts
    quint8 m_qbCount;
    quint8 m_wrCount;
    quint8 m_rbCount;
    quint8 m_teCount;
    quint8 m_flexCount;
    quint8 m_kCount;
    quint8 m_dstCount;
    quint8 m_benchCount;
};
