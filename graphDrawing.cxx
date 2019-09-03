#include <vtkXMLTreeReader.h>
#include <vtkTreeRingView.h>
#include <vtkGraphLayoutView.h>
#include <vtkSmartPointer.h> 
#include <vtkTreeLayoutStrategy.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkHierarchicalGraphView.h>
#include <vtkViewTheme.h>
#include <vtkRenderWindow.h>
  //vtkSmartPointer<type> name = vtkSmartPointer<type>::New();
int main(){
auto XMLReader = vtkSmartPointer<vtkXMLTreeReader>::New();
auto graphReader =vtkSmartPointer<vtkXMLTreeReader>::New();
auto TreeView = vtkSmartPointer<vtkTreeRingView>::New();
//auto treeStrat = vtkSmartPointer<vtkGraphLayoutView>::New();
auto theme = vtkViewTheme::CreateNeonTheme();

//Create xml reader
//xmlRootDir = VTK_DATA_ROOT + "/Data/Infovis/XML/"
XMLReader->SetFileName("./vtkclasses.xml");
XMLReader->SetEdgePedigreeIdArrayName("tree edge");
XMLReader->GenerateVertexPedigreeIdsOff();
XMLReader->SetVertexPedigreeIdArrayName("id");
//create graph readerxml

graphReader->SetFileName("./vtklibrary.xml");
graphReader->SetEdgePedigreeIdArrayName("graph edge");
graphReader->GenerateVertexPedigreeIdsOff();
graphReader->SetVertexPedigreeIdArrayName("id");
graphReader->Update();
//print(graphReader.GetOutput());

//Create a tree layout strategy
//treeStrat->RadialOn();
//treeStrat->setAngle(360);
//treeStrat->SetLogSpacingValue(1);

//head off tree to the tree view
TreeView->SetTreeFromInputConnection(XMLReader->GetOutputPort());
TreeView->SetGraphFromInputConnection(graphReader->GetOutputPort());
TreeView->SetAreaLabelArrayName("id");
TreeView->SetAreaColorArrayName("VertexDegree");
TreeView->SetAreaHoverArrayName("id");
TreeView->SetAreaLabelVisibility(true);
TreeView->SetShrinkPercentage(0.02);
TreeView->SetBundlingStrength(.75);
TreeView->Update();
TreeView->SetEdgeColorArrayName("graph edge");
TreeView->SetColorEdges(true);

//apply theme to the view

theme->SetLineWidth(2);
theme->SetPointSize(10);
theme->SetSelectedCellColor(1,1,1);
theme->SetSelectedPointColor(1,1,1);
TreeView->ApplyViewTheme(theme);

  
theme->FastDelete();
auto renderWindow = TreeView->GetRenderWindow();
renderWindow->SetSize(680,680);
TreeView->ResetCamera();
TreeView->Render();

auto window = TreeView ->GetInteractor();
window->Start();
return 0;
 
}
