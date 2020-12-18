#pragma once
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QFileDialog>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QProcess>
#include <vector>

class MyWindow : public QWidget
{
    QLabel *m_enterSizeLabel;
    QLineEdit *m_sizeLineEdit;
    QPushButton *m_createButton;
    QPushButton *m_randomizeButton;
    QPushButton *m_printButton;
    QPushButton *m_saveButton;
    QLabel *m_info;

    void *m_massive;
    std::vector<int> m_sizes;

    void deleteMassive();

    void randomizeButton();

    void createButton();

    void printButton();

    void saveButton();
public:
    MyWindow(QWidget *parent = nullptr);

    ~MyWindow();
};