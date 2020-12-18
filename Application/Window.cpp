#include "Window.hpp"

MyWindow::MyWindow(QWidget *parent) : QWidget(parent)
{
    m_enterSizeLabel = new QLabel("Введите размер:",this);
    m_enterSizeLabel->setGeometry(20,10,200,20);
    m_enterSizeLabel->show();

    m_sizeLineEdit = new QLineEdit(this);
    m_sizeLineEdit->setGeometry(20,40,200,25);
    m_sizeLineEdit->show();

    m_createButton = new QPushButton("Создать",this);
    m_createButton->setGeometry(230,40,125,25);
    QPushButton::connect(m_createButton,&QPushButton::clicked,this,&MyWindow::createButton);
    m_createButton->show();

    m_printButton = new QPushButton("Вывести",this);
    m_printButton->setGeometry(365,40,125,25);
    QPushButton::connect(m_printButton,&QPushButton::clicked,this,&MyWindow::printButton);
    m_printButton->show();

    m_randomizeButton = new QPushButton("Рандомизировать",this);
    m_randomizeButton->setGeometry(230,75,125,25);
    QPushButton::connect(m_randomizeButton,&QPushButton::clicked,this,&MyWindow::randomizeButton);
    m_randomizeButton->show();

    m_saveButton = new QPushButton("Сохранить",this);
    m_saveButton->setGeometry(365,75,125,25);
    QPushButton::connect(m_saveButton,&QPushButton::clicked,this,&MyWindow::saveButton);
    m_saveButton->show();

    m_info = new QLabel(this);
    m_info->setGeometry(20,100,460,50);
    m_info->setAlignment(Qt::AlignTop);
    m_info->show();

    this->setWindowTitle("Приложение");
    this->setFixedSize(500,175);
    this->show();
}

MyWindow::~MyWindow()
{
    delete m_enterSizeLabel;
    delete m_sizeLineEdit;
    delete m_createButton;
    delete m_info;

    deleteMassive();
}

void MyWindow::createButton()
{
    deleteMassive();
    m_sizes.clear();

    QStringList list;

    if(m_sizeLineEdit->text().trimmed().isEmpty())
    {
        m_info->setText("В поле ввода пусто!");
    }
    else
    {
        list = m_sizeLineEdit->text().endsWith(' ') ? m_sizeLineEdit->text().mid(0,m_sizeLineEdit->text().length()-2).split(' ') : m_sizeLineEdit->text().split(' ');
        for(int i = 0;i<list.size();i++)
            m_sizes.push_back(list[i].toInt());

        if(m_sizes.size() == 1)
            m_massive = (void*)new int[m_sizes[0]]();
        else if(m_sizes.size() == 2)
        {
            m_massive = (void*)new int*[m_sizes[0]]();
            for(int i = 0;i<m_sizes[0];i++)
                ((int**)m_massive)[i] = new int[m_sizes[1]]();
        }
        
        
        m_info->setText("Создан "+ QString::number(m_sizes.size()) + " мерный массив");
    }   

}

void MyWindow::randomizeButton()
{
    if(m_sizes.size() == 1)
        for(int i = 0;i<m_sizes[0];i++)
            ((int*)m_massive)[i] = std::rand() % 250;
    else if(m_sizes.size() == 2)
        for(int i = 0;i<m_sizes[0];i++)
            for(int j = 0;j<m_sizes[1];j++)
                ((int**)m_massive)[i][j] = std::rand() % 250;
}

void MyWindow::printButton()
{
    QString info;

    if(m_sizes.size() == 1)
    {
        for(int i = 0;i<m_sizes[0];i++)
            info += QString::number(((int*)m_massive)[i]) + " "; 
    }
    else if(m_sizes.size() == 2)
        for(int i = 0;i<m_sizes[0];i++)
        {
            for(int j = 0;j<m_sizes[1];j++)
                info += QString::number(((int**)m_massive)[i][j]) + " "; 

            info += '\n';
        }

    m_info->setText(info);
}

void MyWindow::saveButton()
{
    QString info;

    if(m_sizes.size() == 1)
    {
        for(int i = 0;i<m_sizes[0];i++)
            info += QString::number(((int*)m_massive)[i]) + " "; 
    }
    else if(m_sizes.size() == 2)
        for(int i = 0;i<m_sizes[0];i++)
		{
            for(int j = 0;j<m_sizes[1];j++)
                info += QString::number(((int**)m_massive)[i][j]) + " "; 
				
			info += '\n';
		}

    QUrl fileUrl = QFileDialog::getSaveFileUrl(this);
    QFile file(fileUrl.path().mid(1));
    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        stream << info;
        file.close();
        m_info->setText("Сохранено в : "+fileUrl.path().mid(1));

        QProcess *textFile = new QProcess(this);
        textFile->execute("notepad "+fileUrl.path().mid(1));
        textFile->waitForFinished();
        delete textFile;
    }
    else
        m_info->setText("Не удалось сохранить!");
}

void MyWindow::deleteMassive()
{
    if(m_sizes.size() == 1)
            delete[] (int*)m_massive;
    else if(m_sizes.size() == 2)
    {
        for(int i = 0;i<m_sizes[0];i++)
            delete[] ((int**)m_massive)[i];

        delete[] ((int**)m_massive);
    }
}