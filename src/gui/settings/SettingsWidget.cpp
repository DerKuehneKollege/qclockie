//
// Created by mumpi on 05.05.2016.
//

#include <QtCore/QDebug>
#include <QtWidgets/QStyle>
#include <QtWidgets/QDesktopWidget>

#include "SettingsWidget.h"

SettingsWidget::SettingsWidget(QWidget *parent) : QWidget(parent), ui(new Ui::SettingsWidget) {
    ui->setupUi(this);

    // center window
    setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            size(),
            qApp->desktop()->availableGeometry()
        )
    );

    // init state of ui elements
    ui->selectLocationButton->setEnabled(false);

    // connect events
    connect(ui->searchLocationButton, SIGNAL(clicked()), this, SLOT(searchWeatherLocation()));
    connect(ui->selectLocationButton, SIGNAL(clicked()), this, SLOT(selectWeatherLocation()));
    connect(ui->weatherLocationComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(weatherLocationChanged(int)));

    weatherProvider = nullptr;
}

SettingsWidget::~SettingsWidget() {
    delete ui;
}

void SettingsWidget::searchWeatherLocation() {
    QString queryString = ui->weatherLocationComboBox->currentText();
    qDebug() << "Searching location:" << queryString;

    // lazy initialization and event assigning of the weather provider
    if (weatherProvider == nullptr) {
        qFatal("No weather provider initialized!");
        return;
    }

    // deactivate ui button and change caption
    ui->searchLocationButton->setEnabled(false);
    ui->searchLocationButton->setText(tr("Suche läuft..."));

    weatherProvider->sendSearchLocationRequest(queryString);
}

void SettingsWidget::handleSearchWeatherLocationResponse(QList<LocationData>* locationDataList) {
    // fill combobox with values
    ui->weatherLocationComboBox->clear();
    foreach (const LocationData &locationData, *locationDataList) {
        QString comboBoxText = QString("%1, %2, %3")
                .arg(locationData.city)
                .arg(locationData.region)
                .arg(locationData.country);
        ui->weatherLocationComboBox->addItem(comboBoxText, locationData.woeid);
    }

    delete locationDataList;

    // enable ui button and restore caption
    ui->searchLocationButton->setEnabled(true);
    ui->searchLocationButton->setText(tr("Suchen"));
}

void SettingsWidget::handleSearchWeatherLocationError(QString errorString) {
    qDebug() << "Searching location failed:" << errorString;

    // TODO report error in UI

    // enable ui button and restore caption
    ui->searchLocationButton->setEnabled(true);
    ui->searchLocationButton->setText(tr("Suchen"));
}

void SettingsWidget::selectWeatherLocation() {
    // QVariant(Invalid) when nothing selected
    // QVariant(QString, "643099")

    QVariant selectedWeatherLocation = ui->weatherLocationComboBox->currentData();

    if (!selectedWeatherLocation.isValid()) {
        qDebug() << "No weather location selected.";
        return;
    }

    QString selectedWoeid = selectedWeatherLocation.toString();
    QString selectedWeatherLocationString = ui->weatherLocationComboBox->itemText(ui->weatherLocationComboBox->currentIndex());

    qDebug() << "Selected weather location" << selectedWeatherLocationString << "with woeid" << selectedWoeid;
    ui->selectedLocationLabel->setText(tr("Ausgewählter Ort: ") + selectedWeatherLocationString);

    ui->selectLocationButton->setEnabled(false);

    // TODO use same weather provider as the one in the MainWindow
    weatherProvider->setWoeid(selectedWoeid);
    weatherProvider->setLocationString(selectedWeatherLocationString);
    weatherProvider->sendWeatherRequest();
}

void SettingsWidget::weatherLocationChanged(int index) {
    // activate "select location" button if valid weather location is selected,
    // deactivate otherwise
    ui->selectLocationButton->setEnabled(
        index >= 0 && ui->weatherLocationComboBox->currentData().isValid()
    );
}

void SettingsWidget::setWeatherProvider(YahooWeatherProvider *weatherProvider) {
    // TODO must only be run once
    // TODO disconnect on delete
    this->weatherProvider = weatherProvider;
    connect(
        this->weatherProvider,
        SIGNAL(locationSearchResultAvailable(QList<LocationData>*)),
        this,
        SLOT(handleSearchWeatherLocationResponse(QList<LocationData>*))
    );
    connect(
        this->weatherProvider,
        SIGNAL(locationSearchFailed(QString)),
        this,
        SLOT(handleSearchWeatherLocationError(QString))
    );

    this->ui->selectedLocationLabel->setText(tr("Ausgewählter Ort: ") + weatherProvider->getLocationString());
}


