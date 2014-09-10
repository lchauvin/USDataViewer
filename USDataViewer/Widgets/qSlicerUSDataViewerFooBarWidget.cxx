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

// FooBar Widgets includes
#include "qSlicerUSDataViewerFooBarWidget.h"
#include "ui_qSlicerUSDataViewerFooBarWidget.h"

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_USDataViewer
class qSlicerUSDataViewerFooBarWidgetPrivate
  : public Ui_qSlicerUSDataViewerFooBarWidget
{
  Q_DECLARE_PUBLIC(qSlicerUSDataViewerFooBarWidget);
protected:
  qSlicerUSDataViewerFooBarWidget* const q_ptr;

public:
  qSlicerUSDataViewerFooBarWidgetPrivate(
    qSlicerUSDataViewerFooBarWidget& object);
  virtual void setupUi(qSlicerUSDataViewerFooBarWidget*);
};

// --------------------------------------------------------------------------
qSlicerUSDataViewerFooBarWidgetPrivate
::qSlicerUSDataViewerFooBarWidgetPrivate(
  qSlicerUSDataViewerFooBarWidget& object)
  : q_ptr(&object)
{
}

// --------------------------------------------------------------------------
void qSlicerUSDataViewerFooBarWidgetPrivate
::setupUi(qSlicerUSDataViewerFooBarWidget* widget)
{
  this->Ui_qSlicerUSDataViewerFooBarWidget::setupUi(widget);
}

//-----------------------------------------------------------------------------
// qSlicerUSDataViewerFooBarWidget methods

//-----------------------------------------------------------------------------
qSlicerUSDataViewerFooBarWidget
::qSlicerUSDataViewerFooBarWidget(QWidget* parentWidget)
  : Superclass( parentWidget )
  , d_ptr( new qSlicerUSDataViewerFooBarWidgetPrivate(*this) )
{
  Q_D(qSlicerUSDataViewerFooBarWidget);
  d->setupUi(this);
}

//-----------------------------------------------------------------------------
qSlicerUSDataViewerFooBarWidget
::~qSlicerUSDataViewerFooBarWidget()
{
}
