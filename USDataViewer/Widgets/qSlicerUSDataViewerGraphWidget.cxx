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
};

// --------------------------------------------------------------------------
qSlicerUSDataViewerGraphWidgetPrivate
::qSlicerUSDataViewerGraphWidgetPrivate(
  qSlicerUSDataViewerGraphWidget& object)
  : q_ptr(&object)
{
  this->currentDataNode = NULL;
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
  double numberOfSamples = imageData->GetScalarComponentAsDouble(0,0,0,0);

  // Get Scalar Pointer
  short* scalarPointer = (short*)(imageData->GetScalarPointer());
  scalarPointer++;

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
    xAxis->SetNumberOfValues(numberOfSamples);
    for (int i = 0; i < numberOfSamples; ++i)
      {
      xAxis->SetValue(i,i);
      }
    currentSensorTable->AddColumn(xAxis);

    yAxis->SetName("Value");
    yAxis->SetNumberOfValues(numberOfSamples);
    for (int i = 0; i < numberOfSamples; ++i)
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
