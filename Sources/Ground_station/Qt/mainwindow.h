#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//Adresse Serveur : 10.5.133.185

#include "libraries.h"


class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);

        void CreerLog();
        void qInstallMsgHandler();



    public slots:
        void quitterApp();
        void connexion();
        void on_boutonEnvoyer_clicked();
        void donneesRecues();
        void connecte();
        void deconnecte();
        void erreurSocket(QAbstractSocket::SocketError erreur);
        void deconnexion();
        void envoie_arret_urgence();
        void messageErreur();
        void envoie_message_hello();
        //void receptionDonneesJoyStick();
       // void parserDonneesDrone();
        void stop();
        void parserReception();
        void envoieModeAuto();
        void envoieModeManuel();
        void creationLogs();

    signals:
        void signal_parse();


    private:
        QTcpSocket *socket; // Représente le serveur
        quint16 tailleMessage;
        Ui::MainWindow *ui;
        bool ok;
        QString messageRecu;
        QString message_1;
        QString message_2;
        int batterie_index_1=50;
        int batterie_index_2=50;

};




#endif // MAINWINDOW_H













