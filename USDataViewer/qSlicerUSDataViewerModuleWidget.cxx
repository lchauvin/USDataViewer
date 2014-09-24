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
};

//-----------------------------------------------------------------------------
// qSlicerUSDataViewerModuleWidgetPrivate methods

//-----------------------------------------------------------------------------
qSlicerUSDataViewerModuleWidgetPrivate::qSlicerUSDataViewerModuleWidgetPrivate()
{
}

//-----------------------------------------------------------------------------
qSlicerUSDataViewerModuleWidgetPrivate::~qSlicerUSDataViewerModuleWidgetPrivate()
{
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

  connect(d->USDataNodeSelector, SIGNAL(nodeActivated(vtkMRMLNode*)),
	  this, SLOT(onDataNodeSelected(vtkMRMLNode*)));

  connect(d->AllSamplesCheckbox, SIGNAL(stateChanged(int)),
	  this, SLOT(onAllSamplesChanged(int)));

  connect(d->SampleSpinBox, SIGNAL(valueChanged(double)),
	  this, SLOT(onSampleNumberChanged(double)));

  connect(d->SampleOffsetSpinBox, SIGNAL(valueChanged(double)),
	  this, SLOT(onSampleOffsetChanged(double)));
}

//-----------------------------------------------------------------------------
void qSlicerUSDataViewerModuleWidget::onDataNodeSelected(vtkMRMLNode* selectedNode)
{
  Q_D(qSlicerUSDataViewerModuleWidget);

  if (!selectedNode || (selectedNode == d->UltrasoundGraphWidget->getDataNode()))
    {
    return;
    }
  
  vtkMRMLScalarVolumeNode* dataNode = vtkMRMLScalarVolumeNode::SafeDownCast(selectedNode);
  d->UltrasoundGraphWidget->setDataNode(dataNode);

  d->SampleSpinBox->setValue(d->UltrasoundGraphWidget->getNumberOfDataSamplesUsed());
}

//-----------------------------------------------------------------------------
void qSlicerUSDataViewerModuleWidget::onAllSamplesChanged(int state)
{
  Q_D(qSlicerUSDataViewerModuleWidget);

    d->SampleSpinBox->setEnabled(state == Qt::Unchecked);
    d->SampleOffsetSpinBox->setEnabled(state == Qt::Unchecked);

    if (d->UltrasoundGraphWidget)
      {
      if (state == Qt::Checked)
	{
	d->UltrasoundGraphWidget->useAllSamples(true);
	d->SampleSpinBox->setValue(d->UltrasoundGraphWidget->getNumberOfDataSamplesUsed());
	}
      else
	{
	d->UltrasoundGraphWidget->useAllSamples(false);
	d->UltrasoundGraphWidget->setNumberOfDataSamplesToUse(d->SampleSpinBox->value());
	}
      }
}

//-----------------------------------------------------------------------------
void qSlicerUSDataViewerModuleWidget::onSampleNumberChanged(double nOfSamples)
{
  Q_D(qSlicerUSDataViewerModuleWidget);

  if (d->AllSamplesCheckbox->checkState() == Qt::Unchecked)
    {
    if (d->UltrasoundGraphWidget)
      {
      d->UltrasoundGraphWidget->setNumberOfDataSamplesToUse(nOfSamples);
      }
    }
}

//-----------------------------------------------------------------------------
void qSlicerUSDataViewerModuleWidget::onSampleOffsetChanged(double sampleOffset)
{
  Q_D(qSlicerUSDataViewerModuleWidget);

  if (d->AllSamplesCheckbox->checkState() == Qt::Unchecked)
    {
    if (d->UltrasoundGraphWidget)
      {
      d->UltrasoundGraphWidget->setOffsetOfDataSamples(sampleOffset);
      }
    }
}
