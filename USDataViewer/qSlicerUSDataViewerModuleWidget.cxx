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
};

//-----------------------------------------------------------------------------
// qSlicerUSDataViewerModuleWidgetPrivate methods

//-----------------------------------------------------------------------------
qSlicerUSDataViewerModuleWidgetPrivate::qSlicerUSDataViewerModuleWidgetPrivate()
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
}
