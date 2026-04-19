#ifndef GIFWIDGET_H
#define GIFWIDGET_H

#include <QLabel>
#include <QMovie>

class GifWidget : public QLabel {
    Q_OBJECT
public:
    // Qt Designer için default constructor
    explicit GifWidget(QWidget *parent = nullptr)
        : QLabel(parent), movie(nullptr)
    {
    }

    // Direkt GIF yüklemek için
    explicit GifWidget(const QString &gifPath, QWidget *parent = nullptr)
        : QLabel(parent), movie(nullptr)
    {
        setGif(gifPath);
    }

    void setGif(const QString &path) {
        if (movie) {
            movie->stop();
            delete movie;
        }
        movie = new QMovie(path, QByteArray(), this);
        setMovie(movie);
        movie->start();
    }

    void stop()  { if (movie) movie->stop(); }
    void start() { if (movie) movie->start(); }

private:
    QMovie *movie;
};

#endif // GIFWIDGET_H
