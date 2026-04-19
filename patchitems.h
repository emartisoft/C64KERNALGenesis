#ifndef PATCHITEMS_H
#define PATCHITEMS_H

#include <QList>
#include "carditem.h"

const QList<CardItem> items = {
    { 1, ":/res/pictures/logo1.png",
     "No Patch",
     "Sadece renkleri içeren",
     "Sadece renk bilgilerindeki değişiklik ile kaydedilir.\n\n" },

    { 2, ":/res/pictures/test.gif",
     "Şehir Işıkları",
     "Gece vakti şehrin hareketli caddelerinde uzun pozlama",
     "İstanbul Boğazköprüsü gece çekimi.\n\n30 saniye pozlama süresi "
     "ile araç ışıklarının iz bırakması sağlanmıştır. ISO 100, f/11, "
     "tripod kullanılmıştır. Çekim için özel izin alınmıştır." },

    { 3, ":/images/food.jpg",
     "Lezzetli Kahvaltı",
     "Taze malzemelerle hazırlanmış serpme kahvaltı sofrası",
     "Geleneksel Türk kahvaltısı; beyaz peynir, siyah zeytin, domates, "
     "salatalık, bal, kaymak, sucuk ve yumurtadan oluşan tam bir sofra.\n\n"
     "Tüm malzemeler organik çiftliklerden temin edilmiştir." },

    { 4, ":/res/pictures/test.gif",
     "Qt Widget Geliştirme",
     "Qt ile modern masaüstü uygulama geliştirme teknikleri",
     "Qt Widgets ile cross-platform uygulama geliştirirken dikkat "
     "edilmesi gereken performans ipuçları.\n\n"
     "QAbstractItemModel, custom delegate, QPainter ve stylesheet "
     "kullanımı bu projede ele alınan başlıca konulardır.\n\n"
     "QStackedWidget ile sayfa yönetimi ve QScrollArea ile "
     "kaydırılabilir liste implementasyonu incelenmiştir." },

    { 5, ":/images/travel.jpg",
     "Kapadokya Turu",
     "Balon turu ile görülen peri bacaları ve vadiler",
     "Kapadokya, Nevşehir ilinde yer alan ve UNESCO Dünya Mirası "
     "listesinde bulunan doğal ve tarihi bölgedir.\n\n"
     "Sıcak hava balonu turları her sabah şafakla birlikte başlar. "
     "En iyi dönem Nisan-Haziran ve Eylül-Kasım arasıdır." },

    { 6, ":/images/art.jpg",
     "Modern Sanat Sergisi",
     "Çağdaş sanat galerisinden seçilmiş eserler",
     "İstanbul Modern Sanat Müzesi'nde sergilenen çağdaş Türk "
     "sanatçıların eserleri.\n\nSergi 15 Mart - 15 Haziran tarihleri "
     "arasında açık olacaktır. Giriş ücretsizdir.\n\n"
     "40'tan fazla sanatçının 120 eseri yer almaktadır." },
    };

#endif // PATCHITEMS_H
