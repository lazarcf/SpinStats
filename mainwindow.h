#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include <QMessageBox>
#include <QTableWidget>
#include "settingsform.h"
#include <QStandardItemModel>
#include <memory>

struct player_t {
    QString name;
    QString type;
    int cev;

    player_t () {}
    player_t (QString name, QString type) : name(name), type(type) {}
    player_t (QString & player_name) : name (player_name), type ("recreational") {}

    bool operator==(const player_t & player) {
        return player.name == this->name;
    }
};

struct tourney_t {
    tourney_t () {
        id = 0;
        amt_buyin = 0;
        amt_prize_pool = 0;
    }

    int id;

    QMap<QString, player_t> players;

    QDateTime ts_start;
    QDateTime ts_end;

    float amt_buyin;
    float amt_prize_pool;
};

struct database_t {
    database_t ():
        player_type_model(new QStandardItemModel),
        expression_player_type_model(new QStandardItemModel),
        is_valid (false)
    {}

    QString name;
    QString hero;
    QList<tourney_t> tournies;
    QList<QString> reg_labels;
    std::shared_ptr<QStandardItemModel> player_type_model;
    std::shared_ptr<QStandardItemModel> expression_player_type_model;
    bool is_valid;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //void on_pushButton_clicked();

    void test_slot();

    void launch_settings();

    void showEvent(QShowEvent *event);

    void on_databaseCombo_currentIndexChanged(const QString &arg1);

    void on_regLoadButton_clicked();

    void on_regSaveButton_clicked();

    void on_refreshBtutton_clicked();

    void on_dbSplitButton_clicked();

    void on_getExpressionButton_clicked();

    void on_reg_load_pt4_button_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase m_db;
    SettingsForm m_settings;

    bool m_loading_tournies;

    PSNotesForm * m_notes_form;
    QSet<QPair<QString, QString>> m_regs;

    QMap <QString, database_t> m_databases;

    bool split_db (QString in, QString out, QString dump_file, QList<int> tourney_ids);

    int get_cev(const QList<tourney_t> & tournies);

    void show_textbox(QString);
    void get_tourney_info (tourney_t &);
    void add_tourney_info_to_table (const tourney_t &);

    void clear_info();

    void log(QString msg);

    QList<QString> list_databases();
};

#endif // MAINWINDOW_H
