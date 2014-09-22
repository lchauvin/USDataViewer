/*==============================================================================

  Program: 3D Slicer

  Copyright (c) Kitware Inc.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This file was originally developed by Jean-Christophe Fillion-Robin, Kitware Inc.
  and was partially funded by NIH grant 3P41RR013218-12S1

==============================================================================*/

// Graph Widgets includes
#include "qSlicerUSDataViewerGraphWidget.h"
#include "ui_qSlicerUSDataViewerGraphWidget.h"

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_USDataViewer
class qSlicerUSDataViewerGraphWidgetPrivate
  : public Ui_qSlicerUSDataViewerGraphWidget
{
  Q_DECLARE_PUBLIC(qSlicerUSDataViewerGraphWidget);
protected:
  qSlicerUSDataViewerGraphWidget* const q_ptr;

public:
  qSlicerUSDataViewerGraphWidgetPrivate(
    qSlicerUSDataViewerGraphWidget& object);
  virtual void setupUi(qSlicerUSDataViewerGraphWidget*);

  vtkMRMLNode* currentDataNode;
  bool useAllDataSamples;
  int numberOfSamplesToUse;
  int dataSamplesOffset;
};

// --------------------------------------------------------------------------
qSlicerUSDataViewerGraphWidgetPrivate
::qSlicerUSDataViewerGraphWidgetPrivate(
  qSlicerUSDataViewerGraphWidget& object)
  : q_ptr(&object)
{
  this->currentDataNode = NULL;

  this->useAllDataSamples = true;
  this->numberOfSamplesToUse = 0;
  this->dataSamplesOffset = 0;
}

// --------------------------------------------------------------------------
void qSlicerUSDataViewerGraphWidgetPrivate
::setupUi(qSlicerUSDataViewerGraphWidget* widget)
{
  this->Ui_qSlicerUSDataViewerGraphWidget::setupUi(widget);
}

//-----------------------------------------------------------------------------
// qSlicerUSDataViewerGraphWidget methods

//-----------------------------------------------------------------------------
qSlicerUSDataViewerGraphWidget
::qSlicerUSDataViewerGraphWidget(QWidget* parentWidget)
  : Superclass( parentWidget )
  , d_ptr( new qSlicerUSDataViewerGraphWidgetPrivate(*this) )
{
  Q_D(qSlicerUSDataViewerGraphWidget);
  d->setupUi(this);
}

//-----------------------------------------------------------------------------
qSlicerUSDataViewerGraphWidget
::~qSlicerUSDataViewerGraphWidget()
{
}

//-----------------------------------------------------------------------------
void qSlicerUSDataViewerGraphWidget
::setDataNode(vtkMRMLNode* dataNode)
{
  Q_D(qSlicerUSDataViewerGraphWidget);

  if (!dataNode)
    {
    return;
    }

  currentDataNodeModified(dataNode);
}

//-----------------------------------------------------------------------------
void qSlicerUSDataViewerGraphWidget
::useAllSamples(bool useAll)
{
  Q_D(qSlicerUSDataViewerGraphWidget);

  d->useAllDataSamples = useAll;
}

//-----------------------------------------------------------------------------
void qSlicerUSDataViewerGraphWidget
::setNumberOfDataSamplesToUse(int nOfSamples)
{
  Q_D(qSlicerUSDataViewerGraphWidget);

  d->numberOfSamplesToUse = nOfSamples;
}

//-----------------------------------------------------------------------------
int qSlicerUSDataViewerGraphWidget
::getNumberOfDataSamplesUsed()
{
  Q_D(qSlicerUSDataViewerGraphWidget);

  return d->numberOfSamplesToUse;
}

//-----------------------------------------------------------------------------
void qSlicerUSDataViewerGraphWidget
::setOffsetOfDataSamples(int sampleOffset)
{
  Q_D(qSlicerUSDataViewerGraphWidget);

  d->dataSamplesOffset = sampleOffset;
}

//-----------------------------------------------------------------------------
int qSlicerUSDataViewerGraphWidget
::getOffsetOfDataSamples()
{
  Q_D(qSlicerUSDataViewerGraphWidget);

  return d->dataSamplesOffset;
}

//-----------------------------------------------------------------------------
void qSlicerUSDataViewerGraphWidget
::currentDataNodeModified(vtkMRMLNode* dataNode)
{
  Q_D(qSlicerUSDataViewerGraphWidget);

  if (!dataNode)
    {
    return;
    }

  if (dataNode->IsA("vtkMRMLScalarVolumeNode"))
    {
    vtkMRMLScalarVolumeNode* imageNode = vtkMRMLScalarVolumeNode::SafeDownCast(dataNode);
    if (!imageNode)
      {
      return;
      }
    
    this->qvtkReconnect(d->currentDataNode, 
			dataNode, vtkMRMLScalarVolumeNode::ImageDataModifiedEvent,
			this, SLOT(updateGraphFromImage()));
    
    d->currentDataNode = dataNode;
    }  
}

//-----------------------------------------------------------------------------
void qSlicerUSDataViewerGraphWidget
::updateGraphFromImage()
{  
  Q_D(qSlicerUSDataViewerGraphWidget);

  if (!d->currentDataNode || !d->GraphWidget)
    {
    return;
    }

  vtkMRMLScalarVolumeNode* imageNode = vtkMRMLScalarVolumeNode::SafeDownCast(d->currentDataNode);
  if (!imageNode)
    {
    return;
    }

  vtkImageData* imageData = imageNode->GetImageData();
  if (!imageData)
    {
    return;
    }

  for (int i = 0; i < d->GraphWidget->chart()->GetNumberOfPlots(); ++i)
    {
    d->GraphWidget->chart()->RemovePlot(i);
    }

  // Get number of samples
  double totalNumberOfSamples = imageData->GetScalarComponentAsDouble(0,0,0,0);
  if (d->useAllDataSamples)
    {
    d->numberOfSamplesToUse = totalNumberOfSamples;
    }

  int sampleOffset = 0;
  if (!d->useAllDataSamples)
    {
    if (d->dataSamplesOffset + d->numberOfSamplesToUse > totalNumberOfSamples)
      {
      d->dataSamplesOffset = totalNumberOfSamples - d->numberOfSamplesToUse;
      }
    sampleOffset = d->dataSamplesOffset;
    }

  // Get Scalar Pointer
  short* scalarPointer = (short*)(imageData->GetScalarPointer());
  scalarPointer++;

  for (int i = 0; i < sampleOffset; ++i)
    {
    scalarPointer++;
    }

  // Create new table
  vtkSmartPointer<vtkTable> currentSensorTable =
    vtkSmartPointer<vtkTable>::New();

  vtkSmartPointer<vtkDoubleArray> xAxis =
    vtkSmartPointer<vtkDoubleArray>::New();
  
  vtkSmartPointer<vtkDoubleArray> yAxis = 
    vtkSmartPointer<vtkDoubleArray>::New();

  if (currentSensorTable && xAxis && yAxis)
    {
    currentSensorTable->Initialize();

    xAxis->SetName("Sample");
    xAxis->SetNumberOfValues(d->numberOfSamplesToUse);
    for (int i = 0; i < d->numberOfSamplesToUse; ++i)
      {
      xAxis->SetValue(i,i+sampleOffset);
      }
    currentSensorTable->AddColumn(xAxis);

    yAxis->SetName("Value");
    yAxis->SetNumberOfValues(d->numberOfSamplesToUse);
    for (int i = 0; i < d->numberOfSamplesToUse; ++i)
      {
      yAxis->SetValue(i, *scalarPointer);
      scalarPointer++;
      }
    currentSensorTable->AddColumn(yAxis);
    currentSensorTable->Modified();

    vtkChartXY* chartXY = d->GraphWidget->chart();
    chartXY->GetAxis(1)->SetTitle("Sample");
    chartXY->GetAxis(0)->SetTitle("Value");
    chartXY->SetShowLegend(false);

    vtkPlot* newLine = d->GraphWidget->chart()->AddPlot(vtkChart::LINE);
    if (newLine)
      {
      newLine->SetInputData(currentSensorTable.GetPointer(), 0, 1);
      newLine->SetColor(0.0, 0.0, 1.0);
      d->GraphWidget->chart()->RecalculateBounds();
      this->repaint();
      }
    }
}
