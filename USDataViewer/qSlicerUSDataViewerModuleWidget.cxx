/*==============================================================================

  Program: 3D Slicer

  Portions (c) Copyright Brigham and Women's Hospital (BWH) All Rights Reserved.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

==============================================================================*/

// Qt includes
#include <QDebug>

// SlicerQt includes
#include "qSlicerUSDataViewerModuleWidget.h"
#include "ui_qSlicerUSDataViewerModuleWidget.h"

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_ExtensionTemplate
class qSlicerUSDataViewerModuleWidgetPrivate: public Ui_qSlicerUSDataViewerModuleWidget
{
public:
  qSlicerUSDataViewerModuleWidgetPrivate();
  ~qSlicerUSDataViewerModuleWidgetPrivate();

  qSlicerUSDataViewerGraphWidget* GraphDialogWidget;
};

//-----------------------------------------------------------------------------
// qSlicerUSDataViewerModuleWidgetPrivate methods

//-----------------------------------------------------------------------------
qSlicerUSDataViewerModuleWidgetPrivate::qSlicerUSDataViewerModuleWidgetPrivate()
{
  this->GraphDialogWidget = NULL;
}

//-----------------------------------------------------------------------------
qSlicerUSDataViewerModuleWidgetPrivate::~qSlicerUSDataViewerModuleWidgetPrivate()
{
  if (this->GraphDialogWidget)
    {
    this->GraphDialogWidget->deleteLater();
    }
}

//-----------------------------------------------------------------------------
// qSlicerUSDataViewerModuleWidget methods

//-----------------------------------------------------------------------------
qSlicerUSDataViewerModuleWidget::qSlicerUSDataViewerModuleWidget(QWidget* _parent)
  : Superclass( _parent )
  , d_ptr( new qSlicerUSDataViewerModuleWidgetPrivate )
{
}

//-----------------------------------------------------------------------------
qSlicerUSDataViewerModuleWidget::~qSlicerUSDataViewerModuleWidget()
{
}

//-----------------------------------------------------------------------------
void qSlicerUSDataViewerModuleWidget::setup()
{
  Q_D(qSlicerUSDataViewerModuleWidget);
  d->setupUi(this);
  this->Superclass::setup();

  connect(d->ShowGraphButton, SIGNAL(clicked()),
	  this, SLOT(onShowGraphClicked()));

  connect(d->AllSamplesCheckbox, SIGNAL(stateChanged(int)),
	  this, SLOT(onAllSamplesChanged(int)));

  connect(d->SampleSpinBox, SIGNAL(valueChanged(double)),
	  this, SLOT(onSampleNumberChanged(double)));

  connect(d->SampleOffsetSpinBox, SIGNAL(valueChanged(double)),
	  this, SLOT(onSampleOffsetChanged(double)));
}

//-----------------------------------------------------------------------------
void qSlicerUSDataViewerModuleWidget::onShowGraphClicked()
{
  Q_D(qSlicerUSDataViewerModuleWidget);

  if (!d->GraphDialogWidget)
    {
    d->GraphDialogWidget = new qSlicerUSDataViewerGraphWidget(this);
    d->GraphDialogWidget->setDataNode(d->USDataNodeSelector->currentNode());

    d->SampleSpinBox->setValue(d->GraphDialogWidget->getNumberOfDataSamplesUsed());
    }

  connect(d->USDataNodeSelector, SIGNAL(nodeActivated(vtkMRMLNode*)),
	  d->GraphDialogWidget, SLOT(setDataNode(vtkMRMLNode*)));

  d->GraphDialogWidget->show();
}

//-----------------------------------------------------------------------------
void qSlicerUSDataViewerModuleWidget::onAllSamplesChanged(int state)
{
  Q_D(qSlicerUSDataViewerModuleWidget);

    d->SampleSpinBox->setEnabled(state == Qt::Unchecked);
    d->SampleOffsetSpinBox->setEnabled(state == Qt::Unchecked);

    if (d->GraphDialogWidget)
      {
      if (state == Qt::Checked)
	{
	d->GraphDialogWidget->useAllSamples(true);
	d->SampleSpinBox->setValue(d->GraphDialogWidget->getNumberOfDataSamplesUsed());
	}
      else
	{
	d->GraphDialogWidget->useAllSamples(false);
	d->GraphDialogWidget->setNumberOfDataSamplesToUse(d->SampleSpinBox->value());
	}
      }
}

//-----------------------------------------------------------------------------
void qSlicerUSDataViewerModuleWidget::onSampleNumberChanged(double nOfSamples)
{
  Q_D(qSlicerUSDataViewerModuleWidget);

  if (d->AllSamplesCheckbox->checkState() == Qt::Unchecked)
    {
    if (d->GraphDialogWidget)
      {
      d->GraphDialogWidget->setNumberOfDataSamplesToUse(nOfSamples);
      }
    }
}

//-----------------------------------------------------------------------------
void qSlicerUSDataViewerModuleWidget::onSampleOffsetChanged(double sampleOffset)
{
  Q_D(qSlicerUSDataViewerModuleWidget);

  if (d->AllSamplesCheckbox->checkState() == Qt::Unchecked)
    {
    if (d->GraphDialogWidget)
      {
      d->GraphDialogWidget->setOffsetOfDataSamples(sampleOffset);
      }
    }
}
