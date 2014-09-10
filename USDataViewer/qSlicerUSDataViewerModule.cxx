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
#include <QtPlugin>

// USDataViewer Logic includes
#include <vtkSlicerUSDataViewerLogic.h>

// USDataViewer includes
#include "qSlicerUSDataViewerModule.h"
#include "qSlicerUSDataViewerModuleWidget.h"

//-----------------------------------------------------------------------------
Q_EXPORT_PLUGIN2(qSlicerUSDataViewerModule, qSlicerUSDataViewerModule);

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_ExtensionTemplate
class qSlicerUSDataViewerModulePrivate
{
public:
  qSlicerUSDataViewerModulePrivate();
};

//-----------------------------------------------------------------------------
// qSlicerUSDataViewerModulePrivate methods

//-----------------------------------------------------------------------------
qSlicerUSDataViewerModulePrivate::qSlicerUSDataViewerModulePrivate()
{
}

//-----------------------------------------------------------------------------
// qSlicerUSDataViewerModule methods

//-----------------------------------------------------------------------------
qSlicerUSDataViewerModule::qSlicerUSDataViewerModule(QObject* _parent)
  : Superclass(_parent)
  , d_ptr(new qSlicerUSDataViewerModulePrivate)
{
}

//-----------------------------------------------------------------------------
qSlicerUSDataViewerModule::~qSlicerUSDataViewerModule()
{
}

//-----------------------------------------------------------------------------
QString qSlicerUSDataViewerModule::helpText() const
{
  return "This is a loadable module that can be bundled in an extension";
}

//-----------------------------------------------------------------------------
QString qSlicerUSDataViewerModule::acknowledgementText() const
{
  return "This work was partially funded by NIH grant NXNNXXNNNNNN-NNXN";
}

//-----------------------------------------------------------------------------
QStringList qSlicerUSDataViewerModule::contributors() const
{
  QStringList moduleContributors;
  moduleContributors << QString("John Doe (AnyWare Corp.)");
  return moduleContributors;
}

//-----------------------------------------------------------------------------
QIcon qSlicerUSDataViewerModule::icon() const
{
  return QIcon(":/Icons/USDataViewer.png");
}

//-----------------------------------------------------------------------------
QStringList qSlicerUSDataViewerModule::categories() const
{
  return QStringList() << "Examples";
}

//-----------------------------------------------------------------------------
QStringList qSlicerUSDataViewerModule::dependencies() const
{
  return QStringList();
}

//-----------------------------------------------------------------------------
void qSlicerUSDataViewerModule::setup()
{
  this->Superclass::setup();
}

//-----------------------------------------------------------------------------
qSlicerAbstractModuleRepresentation* qSlicerUSDataViewerModule
::createWidgetRepresentation()
{
  return new qSlicerUSDataViewerModuleWidget;
}

//-----------------------------------------------------------------------------
vtkMRMLAbstractLogic* qSlicerUSDataViewerModule::createLogic()
{
  return vtkSlicerUSDataViewerLogic::New();
}
