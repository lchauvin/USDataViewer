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

#ifndef __qSlicerUSDataViewerGraphWidget_h
#define __qSlicerUSDataViewerGraphWidget_h

// Qt includes
#include <QDialog>

#include "vtkAxis.h"
#include "vtkChartXY.h"
#include "vtkDoubleArray.h"
#include "vtkPlot.h"
#include "vtkTable.h"

#include "vtkImageData.h"

#include "vtkMRMLNode.h"
#include "vtkMRMLScalarVolumeNode.h"

// Graph Widgets includes
#include "qSlicerUSDataViewerModuleWidgetsExport.h"

#include "ctkVTKObject.h"

class qSlicerUSDataViewerGraphWidgetPrivate;

/// \ingroup Slicer_QtModules_USDataViewer
class Q_SLICER_MODULE_USDATAVIEWER_WIDGETS_EXPORT qSlicerUSDataViewerGraphWidget
: public QDialog
{
  Q_OBJECT
  QVTK_OBJECT

public:
  typedef QDialog Superclass;
  qSlicerUSDataViewerGraphWidget(QWidget *parent=0);
  virtual ~qSlicerUSDataViewerGraphWidget();

  void currentDataNodeModified(vtkMRMLNode* dataNode);

protected slots:
  void setDataNode(vtkMRMLNode* dataNode);
  void updateGraphFromImage();

protected:
  QScopedPointer<qSlicerUSDataViewerGraphWidgetPrivate> d_ptr;

private:
  Q_DECLARE_PRIVATE(qSlicerUSDataViewerGraphWidget);
  Q_DISABLE_COPY(qSlicerUSDataViewerGraphWidget);
};

#endif
