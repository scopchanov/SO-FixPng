/**
MIT License

Copyright (c) 2018 Michael Scopchanov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "MainWindow.h"
#include <QPushButton>
#include <QFileDialog>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)
{
	setCentralWidget(new QPushButton(tr("Fix Image"), this));

	connect(static_cast<QPushButton *>(centralWidget()), &QPushButton::clicked, [this](){
		QString fileNameIn(QFileDialog::getOpenFileName(this, tr("Select Image"), ".", "*.png"));

		if (fileNameIn.isEmpty())
			return;

		QString fileNameOut(QFileDialog::getSaveFileName(this, tr("Save Image As..."),
														 fileNameIn.replace(".png", "_fixed.png"),
														 "*.png"));

		if (fileNameOut.isEmpty())
			return;

		QPixmap pixmap;
		pixmap.load(fileNameIn);

		QFile file(fileNameOut);
		file.open(QIODevice::WriteOnly);
		pixmap.save(&file, "PNG");
		file.close();
	});
}
