/***************************************************************************
                          addconstraintstudentsmingapsbetweenbuildingchangesform.cpp  -  description
                             -------------------
    begin                : Feb 10, 2005
    copyright            : (C) 2005 by Lalescu Liviu
    email                : Please see https://lalescu.ro/liviu/ for details about contacting Liviu Lalescu (in particular, you can find here the e-mail address)
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software: you can redistribute it and/or modify  *
 *   it under the terms of the GNU Affero General Public License as        *
 *   published by the Free Software Foundation, either version 3 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/

#include <QMessageBox>

#include "longtextmessagebox.h"

#include "addconstraintstudentsmingapsbetweenbuildingchangesform.h"
#include "spaceconstraint.h"

AddConstraintStudentsMinGapsBetweenBuildingChangesForm::AddConstraintStudentsMinGapsBetweenBuildingChangesForm(QWidget* parent): QDialog(parent)
{
	setupUi(this);

	addConstraintPushButton->setDefault(true);

	connect(addConstraintPushButton, SIGNAL(clicked()), this, SLOT(addCurrentConstraint()));
	connect(closePushButton, SIGNAL(clicked()), this, SLOT(close()));

	centerWidgetOnScreen(this);
	restoreFETDialogGeometry(this);
		
	minGapsSpinBox->setMinimum(1);
	minGapsSpinBox->setMaximum(gt.rules.nHoursPerDay);
	minGapsSpinBox->setValue(1);
	
	constraintChanged();
}

AddConstraintStudentsMinGapsBetweenBuildingChangesForm::~AddConstraintStudentsMinGapsBetweenBuildingChangesForm()
{
	saveFETDialogGeometry(this);
}

void AddConstraintStudentsMinGapsBetweenBuildingChangesForm::constraintChanged()
{
}

void AddConstraintStudentsMinGapsBetweenBuildingChangesForm::addCurrentConstraint()
{
	SpaceConstraint *ctr=NULL;

	double weight;
	QString tmp=weightLineEdit->text();
	weight_sscanf(tmp, "%lf", &weight);
	if(weight<100.0 || weight>100.0){
		QMessageBox::warning(this, tr("FET information"),
			tr("Invalid weight (percentage). It has to be 100"));
		return;
	}

	ctr=new ConstraintStudentsMinGapsBetweenBuildingChanges(weight, minGapsSpinBox->value());

	bool tmp2=gt.rules.addSpaceConstraint(ctr);
	if(tmp2)
		LongTextMessageBox::information(this, tr("FET information"),
			tr("Constraint added:")+"\n\n"+ctr->getDetailedDescription(gt.rules));
	else{
		QMessageBox::warning(this, tr("FET information"),
			tr("Constraint NOT added - please report error"));
		delete ctr;
	}
}
