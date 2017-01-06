#include "GUI.h"
#include "DiamondSquare.h"
#include "TerrainHelper.h"
#include "Settings.h"

GUI::GUI(Renderer &renderer) : m_renderer(renderer) {

	m_desktop.Add(initGUIWindow());
	m_desktop.Add(initCommandWindow());
}


GUI::~GUI(void) {
}

void GUI::updateNoiseSeed() {
	Settings::noiseSeed = atof(m_noiseSeedBox->GetVisibleText().toAnsiString().c_str());
}
void GUI::updateCornerSeed() {
	Settings::cornerSeed = atof(m_cornerSeedBox->GetVisibleText().toAnsiString().c_str());
}

void GUI::updateTessInner() {
	Settings::tessLevelInner = m_tessInnerScale->GetValue();
}

void GUI::updateTessOuter() {
	Settings::tessLevelOuter = m_tessOuterScale->GetValue();
}

void GUI::updateSmoothing() {
	Settings::smoothingScale = m_smoothingScale->GetValue();
}

void GUI::updateMountainHeight() {
	Settings::mountainScale = m_mountainScale->GetValue();
}

void GUI::randomise() {
	//cout << "asd" << endl;
}

void GUI::updateWaterScale() {
	Settings::waterScale = m_waterScale->GetValue();
}

void GUI::updateRipple() {
	Settings::rippleIntensity = m_rippleScale->GetValue();
}

void GUI::updateTransparency() {
	Settings::transparency = m_transparencyScale->GetValue();
}

void GUI::updateWaterRed() {
	Settings::waterRed = m_waterRedScale->GetValue();
}

void GUI::updateWaterGreen() {
	Settings::waterGreen = m_waterGreenScale->GetValue();
}

void GUI::updateWaterBlue() {
	Settings::waterBlue = m_waterBlueScale->GetValue();
}

void GUI::updateRadiusScale() {
	Settings::radius = m_radiusScale->GetValue();
	updateLight();
}

void GUI::updateLightRed() {
	Settings::lightRed = m_lightRedScale->GetValue();
	updateLight();
}

void GUI::updateLightGreen() {
	Settings::lightGreen = m_lightGreenScale->GetValue();
	updateLight();
}

void GUI::updateLightBlue() {
	Settings::lightBlue = m_lightBlueScale->GetValue();
	updateLight();
}

void GUI::updateLight() {
	m_renderer.getLight().SetColour(glm::vec4(Settings::lightRed, Settings::lightGreen, Settings::lightBlue, 0.0f));
	m_renderer.getLight().SetRadius(Settings::radius);
}

void GUI::updateWireframe() {
	Settings::isWireMode = !Settings::isWireMode;
}

void GUI::updateGroundTypeScale () {
	Settings::groundTypeScale = m_groundTypeScale->GetValue();
}

void GUI::updateThermal() {
	Settings::hasThermalErosion = !Settings::hasThermalErosion;
}

void GUI::generateWorld() {
	int size = m_dataSizeCombo->GetSelectedItem();
	switch (size) {
		case 0:
			Settings::dataSize = 129;
			break;
		case 1:
			Settings::dataSize = 257;
			break;
		case 2:
			Settings::dataSize = 513;
			break;
		case 3:
			Settings::dataSize = 1025;
			break;
		case 4:
			Settings::dataSize = 2049;
			break;
		default:
			Settings::dataSize = 129;
	}

	DiamondSquare heightMapIcon("heightmapIcon", 129, Settings::noiseSeed, Settings::cornerSeed, 32);
	TerrainHelper::smoothTerrain(heightMapIcon.getData(), heightMapIcon.getDataSize(), 5, Settings::smoothingScale);
	heightMapIcon.saveToBitmap();	

	DiamondSquare heightMap("heightmap", Settings::dataSize, Settings::noiseSeed, Settings::cornerSeed, 32);
	TerrainHelper::smoothTerrain(heightMap.getData(), heightMap.getDataSize(), 5, Settings::smoothingScale);
	heightMap.saveToBitmap();

	sf::Image image;
	image.loadFromFile("heightmapIcon.bmp");
	m_heightmapImage->SetImage(image);

	m_renderer.updateTexture();
}

void GUI::importSettings() {
	Settings::load();
	reload();
}

void GUI::reload() {
	m_noiseSeedBox->SetText(std::to_string(Settings::noiseSeed));
	m_cornerSeedBox->SetText(std::to_string(Settings::cornerSeed));
	m_tessInnerScale->SetValue(Settings::tessLevelInner);
	m_tessOuterScale->SetValue(Settings::tessLevelOuter);
	m_smoothingScale->SetValue(Settings::smoothingScale);
	m_mountainScale->SetValue(Settings::mountainScale);
	m_waterScale->SetValue(Settings::waterScale);
	m_rippleScale->SetValue(Settings::rippleIntensity);
	m_transparencyScale->SetValue(Settings::transparency);
	m_waterRedScale->SetValue(Settings::waterRed);
	m_waterGreenScale->SetValue(Settings::waterGreen);
	m_waterBlueScale->SetValue(Settings::waterBlue);
	m_radiusScale->SetValue(Settings::radius);
	m_lightRedScale->SetValue(Settings::lightRed);
	m_lightGreenScale->SetValue(Settings::lightGreen);
	m_lightBlueScale->SetValue(Settings::lightBlue);
	m_groundTypeScale->SetValue(Settings::groundTypeScale);
	updateLight();

	if(Settings::dataSize == 129) {
		m_dataSizeCombo->SelectItem(0);
	}else if (Settings::dataSize == 257) {
		m_dataSizeCombo->SelectItem(1);
	}else if (Settings::dataSize == 257) {
		m_dataSizeCombo->SelectItem(2);
	}else if (Settings::dataSize == 513) {
		m_dataSizeCombo->SelectItem(3);
	}else if (Settings::dataSize == 1025) {
		m_dataSizeCombo->SelectItem(4);
	}else if (Settings::dataSize == 2049) {
		m_dataSizeCombo->SelectItem(5);
	}else {
		m_dataSizeCombo->SelectItem(0);
	}

	if(Settings::noiseAlgorithm == 0) {
		m_noiseCombo->SelectItem(0);
	}else if (Settings::noiseAlgorithm == 1) {
		m_noiseCombo->SelectItem(1);
	}else {
		m_noiseCombo->SelectItem(0);
	}
}

void GUI::exportSettings() {
	int size = m_dataSizeCombo->GetSelectedItem();
	switch (size) {
		case 0:
			Settings::dataSize = 129;
			break;
		case 1:
			Settings::dataSize = 257;
			break;
		case 2:
			Settings::dataSize = 513;
			break;
		case 3:
			Settings::dataSize = 1025;
			break;
		case 4:
			Settings::dataSize = 2049;
			break;
		default:
			Settings::dataSize = 129;
	}

	updateNoiseSeed();
	updateCornerSeed();

	Settings::save();
}

sfg::Window::Ptr GUI::initGUIWindow() {
	// Create window for gui
	auto window = sfg::Window::Create(sfg::Window::TOPLEVEL );
    window->SetTitle( "CONTROL PANEL" );

	// Create notebook (Tab pane)
	auto notebook = sfg::Notebook::Create();

	notebook->AppendPage( initTessTable(), sfg::Label::Create( "Terrain" ) );
	notebook->AppendPage( initLightTable(), sfg::Label::Create( "Lighting" ) );
	notebook->AppendPage( initWaterTable(), sfg::Label::Create( "Water" ) );
	notebook->AppendPage( initPostTable(), sfg::Label::Create( "Post processing" ) );
	notebook->SetScrollable( true );
	notebook->SetRequisition( sf::Vector2f( 0.f, 0.f ));
	
	// Add notebook to window
	window->Add( notebook );
	
	// Update GUI
	m_noiseSeedBox->SetText(std::to_string(Settings::noiseSeed));
	m_cornerSeedBox->SetText(std::to_string(Settings::cornerSeed));
	m_tessInnerScale->SetValue(Settings::tessLevelInner);
	m_tessOuterScale->SetValue(Settings::tessLevelOuter);
	m_smoothingScale->SetValue(Settings::smoothingScale);
	m_mountainScale->SetValue(Settings::mountainScale);

	m_waterScale->SetValue(Settings::waterScale);
	m_rippleScale->SetValue(Settings::rippleIntensity);
	m_transparencyScale->SetValue(Settings::transparency);
	m_waterRedScale->SetValue(Settings::waterRed);
	m_waterGreenScale->SetValue(Settings::waterGreen);
	m_waterBlueScale->SetValue(Settings::waterBlue);

	m_radiusScale->SetValue(Settings::radius);
	m_lightRedScale->SetValue(Settings::lightRed);
	m_lightGreenScale->SetValue(Settings::lightGreen);
	m_lightBlueScale->SetValue(Settings::lightBlue);

	m_groundTypeScale->SetValue(Settings::groundTypeScale);

	return window;
}

sfg::Window::Ptr GUI::initCommandWindow() {
	// Create window for gui
	auto window = sfg::Window::Create(sfg::Window::TOPLEVEL );
    window->SetTitle( "COMMAND PANEL" );
	window->SetPosition((sf::Vector2f(m_renderer.getWindow().getView().getSize().x - (m_renderer.getWindow().getView().getSize().x / 4), 0)));
	
	// Create table
	auto tblBtns = sfg::Table::Create();
	tblBtns->SetRowSpacings( 5.f );
    tblBtns->SetColumnSpacings( 40.f );

	// Initialise Widgets
	m_generateBtn = sfg::Button::Create("UPDATE");
	m_importBtn = sfg::Button::Create("IMPORT");
	m_exportBtn = sfg::Button::Create("EXPORT");

	// Initialise Handles
	m_generateBtn->GetSignal(sfg::Widget::OnMouseLeftRelease).Connect(&GUI::generateWorld, this);
	m_importBtn->GetSignal(sfg::Widget::OnMouseLeftRelease).Connect(&GUI::importSettings, this);
	m_exportBtn->GetSignal(sfg::Widget::OnMouseLeftRelease).Connect(&GUI::exportSettings, this);

	// Attatch widgets
	tblBtns->Attach( m_generateBtn, sf::Rect<sf::Uint32>( 0, 0, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );
	tblBtns->Attach( m_importBtn, sf::Rect<sf::Uint32>( 0, 8, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );
	tblBtns->Attach( m_exportBtn, sf::Rect<sf::Uint32>( 0, 16, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );

	window->Add( tblBtns );

	return window;
}

sfg::Table::Ptr GUI::initTessTable() {
	// Create a table
	auto tblTess = sfg::Table::Create();
    tblTess->SetRowSpacings( 3.f );
    tblTess->SetColumnSpacings( 40.f );

	// Initialise widgets
	m_tessInnerScale = sfg::Scale::Create( 1.0f, 70.0f, 1.0f, sfg::Scale::Orientation::HORIZONTAL );
    m_tessOuterScale = sfg::Scale::Create( 1.0f, 70.0f, 1.0f, sfg::Scale::Orientation::HORIZONTAL );
	m_smoothingScale = sfg::Scale::Create( 0.0f, 10.0f, 1.0f, sfg::Scale::Orientation::HORIZONTAL );
	m_mountainScale = sfg::Scale::Create( 0.1f, 50.0f, 0.1f, sfg::Scale::Orientation::HORIZONTAL );
	m_thermalCheck = sfg::CheckButton::Create("Enable Thermal Erosion");
	m_noiseCombo = sfg::ComboBox::Create();
	m_noiseCombo->AppendItem("Diamond-Square");
	m_noiseCombo->AppendItem("Perlin");
	m_noiseCombo->SelectItem(0);
	m_noiseSeedBox = sfg::Entry::Create();
	m_cornerSeedBox = sfg::Entry::Create();
	m_dataSizeCombo = sfg::ComboBox::Create();
	m_dataSizeCombo->AppendItem("128");
	m_dataSizeCombo->AppendItem("256");
	m_dataSizeCombo->AppendItem("512");
	m_dataSizeCombo->AppendItem("1024");
	m_dataSizeCombo->AppendItem("2048");
	m_dataSizeCombo->SelectItem(0);
	m_randomiseBtn = sfg::Button::Create("RANDOMISE");

	sf::Image image;
	image.loadFromFile("heightmapIcon.bmp");
	m_heightmapImage = sfg::Image::Create(image);

	// Set up handles
	m_noiseSeedBox->GetSignal(sfg::Widget::OnMouseMove).Connect(&GUI::updateNoiseSeed, this);
	m_cornerSeedBox->GetSignal(sfg::Widget::OnMouseMove).Connect(&GUI::updateCornerSeed, this);
	m_tessInnerScale->GetSignal(sfg::Widget::OnMouseMove).Connect(&GUI::updateTessInner, this);
	m_tessOuterScale->GetSignal(sfg::Widget::OnMouseMove).Connect(&GUI::updateTessOuter, this);
	m_smoothingScale->GetSignal(sfg::Widget::OnMouseMove).Connect(&GUI::updateSmoothing, this);
	m_mountainScale->GetSignal(sfg::Widget::OnMouseMove).Connect(&GUI::updateMountainHeight, this);
	m_randomiseBtn->GetSignal(sfg::Widget::OnMouseLeftRelease).Connect(&GUI::randomise, this);

	// Attach widgets to table
	tblTess->Attach( sfg::Label::Create( "Noise Seed (Update Required):" ), sf::Rect<sf::Uint32>( 0, 0, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );
	tblTess->Attach( m_noiseSeedBox, sf::Rect<sf::Uint32>( 0, 8, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );

	tblTess->Attach( sfg::Label::Create( "Corner Seed (Update Required):" ), sf::Rect<sf::Uint32>( 0, 16, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );
	tblTess->Attach( m_cornerSeedBox, sf::Rect<sf::Uint32>( 0, 24, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );

	tblTess->Attach( sfg::Label::Create( "Tesselation Inner Factor:" ), sf::Rect<sf::Uint32>( 0, 32, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );
	tblTess->Attach( m_tessInnerScale, sf::Rect<sf::Uint32>( 0, 40, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );

	tblTess->Attach( sfg::Label::Create( "Tesselation Outer Factor:" ), sf::Rect<sf::Uint32>( 0, 48, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );
	tblTess->Attach( m_tessOuterScale, sf::Rect<sf::Uint32>( 0, 56, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );

	tblTess->Attach( sfg::Label::Create( "Smoothing Filter (Update Required):" ), sf::Rect<sf::Uint32>( 0, 64, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );
	tblTess->Attach( m_smoothingScale, sf::Rect<sf::Uint32>( 0, 72, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );

	tblTess->Attach( sfg::Label::Create( "Noise Algorithm:" ), sf::Rect<sf::Uint32>( 0, 80, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );
	tblTess->Attach( m_noiseCombo, sf::Rect<sf::Uint32>( 0, 88, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );
	
	tblTess->Attach( sfg::Label::Create( "Mountain Height:" ), sf::Rect<sf::Uint32>( 0, 96, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );
	tblTess->Attach( m_mountainScale, sf::Rect<sf::Uint32>( 0, 104, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );

	tblTess->Attach( sfg::Label::Create( "Data Size (Update Required):" ), sf::Rect<sf::Uint32>( 0, 112, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );
	tblTess->Attach( m_dataSizeCombo, sf::Rect<sf::Uint32>( 0, 120, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );

	tblTess->Attach( sfg::Label::Create( "Thermal Erosion (Update Required):" ), sf::Rect<sf::Uint32>( 0, 128, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );
	tblTess->Attach( m_thermalCheck, sf::Rect<sf::Uint32>( 0, 136, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );

	tblTess->Attach( m_randomiseBtn, sf::Rect<sf::Uint32>( 0, 144, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );

	tblTess->Attach( sfg::Separator::Create( sfg::Separator::Orientation::HORIZONTAL), sf::Rect<sf::Uint32>( 0, 152, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );

	tblTess->Attach( sfg::Label::Create( "Heightmap Thumbnail:" ), sf::Rect<sf::Uint32>( 0, 160, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );
	tblTess->Attach( m_heightmapImage, sf::Rect<sf::Uint32>( 0, 168, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL);

	return tblTess;
}

sfg::Table::Ptr GUI::initWaterTable() {
	// Create a table
	auto tblWater = sfg::Table::Create();
    tblWater->SetRowSpacings( 2.f );
    tblWater->SetColumnSpacings( 70.f );

	// Initialise widgets
	m_waterScale = sfg::Scale::Create( 0.01f, 0.5f, 0.001f, sfg::Scale::Orientation::HORIZONTAL );
	m_rippleScale = sfg::Scale::Create( 1.0f, 4000.0f, 1.0f, sfg::Scale::Orientation::HORIZONTAL );
	m_transparencyScale = sfg::Scale::Create( 0.0f, 1.0f, 0.01f, sfg::Scale::Orientation::HORIZONTAL );
	m_waterRedScale = sfg::Scale::Create( 0.0f, 255.0f, 1.0f, sfg::Scale::Orientation::HORIZONTAL ); 
	m_waterGreenScale = sfg::Scale::Create( 0.0f, 255.0f, 1.0f, sfg::Scale::Orientation::HORIZONTAL );
	m_waterBlueScale = sfg::Scale::Create( 0.0f, 255.0f, 1.0f, sfg::Scale::Orientation::HORIZONTAL );

	// Set up handles
	m_waterScale->GetSignal(sfg::Widget::OnMouseMove).Connect(&GUI::updateWaterScale, this);
	m_rippleScale->GetSignal(sfg::Widget::OnMouseMove).Connect(&GUI::updateRipple, this);
	m_transparencyScale->GetSignal(sfg::Widget::OnMouseMove).Connect(&GUI::updateTransparency, this);
	m_waterRedScale->GetSignal(sfg::Widget::OnMouseMove).Connect(&GUI::updateWaterRed, this);
	m_waterGreenScale->GetSignal(sfg::Widget::OnMouseMove).Connect(&GUI::updateWaterGreen, this);
	m_waterBlueScale->GetSignal(sfg::Widget::OnMouseMove).Connect(&GUI::updateWaterBlue, this);

	// Attach widgets to table
	tblWater->Attach( sfg::Label::Create( "Water Scale:" ), sf::Rect<sf::Uint32>( 0, 0, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );
	tblWater->Attach( m_waterScale, sf::Rect<sf::Uint32>( 0, 8, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );

	tblWater->Attach( sfg::Label::Create( "Ripple Intensity:" ), sf::Rect<sf::Uint32>( 0, 16, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );
	tblWater->Attach( m_rippleScale, sf::Rect<sf::Uint32>( 0, 24, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );

	tblWater->Attach( sfg::Label::Create( "Transparency:" ), sf::Rect<sf::Uint32>( 0, 32, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );
	tblWater->Attach( m_transparencyScale, sf::Rect<sf::Uint32>( 0, 40, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );

	tblWater->Attach( sfg::Frame::Create( "Water Colour" ), sf::Rect<sf::Uint32>( 0, 48, 5, 55 ), sfg::Table::FILL, sfg::Table::FILL );

	tblWater->Attach( sfg::Label::Create( "Red:" ), sf::Rect<sf::Uint32>( 0, 56, 5, 1 ), sfg::Table::FILL, sfg::Table::FILL );
	tblWater->Attach( m_waterRedScale, sf::Rect<sf::Uint32>( 0, 64, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );

	tblWater->Attach( sfg::Label::Create( "Green:" ), sf::Rect<sf::Uint32>( 0, 72, 5, 1 ), sfg::Table::FILL, sfg::Table::FILL );
	tblWater->Attach( m_waterGreenScale, sf::Rect<sf::Uint32>( 0, 80, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );

	tblWater->Attach( sfg::Label::Create( "Blue:" ), sf::Rect<sf::Uint32>( 0, 88, 5, 1 ), sfg::Table::FILL, sfg::Table::FILL );
	tblWater->Attach( m_waterBlueScale, sf::Rect<sf::Uint32>( 0, 96, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );

	return tblWater;
}

sfg::Table::Ptr GUI::initLightTable() {
	// Create a table
	auto tblLight = sfg::Table::Create();
    tblLight->SetRowSpacings( 2.f );
    tblLight->SetColumnSpacings( 70.f );

	// Initialise widgets
	m_radiusScale = sfg::Scale::Create( 0.0f, 500.0f, 1.0f, sfg::Scale::Orientation::HORIZONTAL );
	m_lightRedScale = sfg::Scale::Create( 0.0f, 60.0f, 1.0f, sfg::Scale::Orientation::HORIZONTAL ); 
	m_lightGreenScale = sfg::Scale::Create( 0.0f, 60.0f, 1.0f, sfg::Scale::Orientation::HORIZONTAL );
	m_lightBlueScale = sfg::Scale::Create( 0.0f, 60.0f, 1.0f, sfg::Scale::Orientation::HORIZONTAL );

	// Set up handles
	m_radiusScale->GetSignal(sfg::Widget::OnMouseMove).Connect(&GUI::updateRadiusScale, this);
	m_lightRedScale->GetSignal(sfg::Widget::OnMouseMove).Connect(&GUI::updateLightRed, this);
	m_lightGreenScale->GetSignal(sfg::Widget::OnMouseMove).Connect(&GUI::updateLightGreen, this);
	m_lightBlueScale->GetSignal(sfg::Widget::OnMouseMove).Connect(&GUI::updateLightBlue, this);

	// Attach widgets to table
	tblLight->Attach( sfg::Label::Create( "Light Radius:" ), sf::Rect<sf::Uint32>( 0, 0, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );
	tblLight->Attach( m_radiusScale, sf::Rect<sf::Uint32>( 0, 8, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );

	tblLight->Attach( sfg::Frame::Create( "Light Colour" ), sf::Rect<sf::Uint32>( 0, 16, 5, 55 ), sfg::Table::FILL, sfg::Table::FILL );

	tblLight->Attach( sfg::Label::Create( "Red:" ), sf::Rect<sf::Uint32>( 0, 24, 5, 1 ), sfg::Table::FILL, sfg::Table::FILL );
	tblLight->Attach( m_lightRedScale, sf::Rect<sf::Uint32>( 0, 32, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );

	tblLight->Attach( sfg::Label::Create( "Green:" ), sf::Rect<sf::Uint32>( 0, 40, 5, 1 ), sfg::Table::FILL, sfg::Table::FILL );
	tblLight->Attach( m_lightGreenScale, sf::Rect<sf::Uint32>( 0, 48, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );

	tblLight->Attach( sfg::Label::Create( "Blue:" ), sf::Rect<sf::Uint32>( 0, 56, 5, 1 ), sfg::Table::FILL, sfg::Table::FILL );
	tblLight->Attach( m_lightBlueScale, sf::Rect<sf::Uint32>( 0, 64, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );

	return tblLight;
}

sfg::Table::Ptr GUI::initPostTable() {
	// Create a table
	auto tblPost = sfg::Table::Create();
    tblPost->SetRowSpacings( 3.f );
    tblPost->SetColumnSpacings( 40.f );

	// Initialise widgets
	m_wireframeCheck = sfg::CheckButton::Create("Enable Wireframe");
	m_toonCheck = sfg::CheckButton::Create("Enable Toon Shader");
	m_groundTypeScale = sfg::Scale::Create( 0.0f, 1.0f, 0.001f, sfg::Scale::Orientation::HORIZONTAL );

	// Set up handles
	m_wireframeCheck->GetSignal(sfg::Widget::OnMouseLeftRelease).Connect(&GUI::updateWireframe, this);
	m_groundTypeScale->GetSignal(sfg::Widget::OnMouseMove).Connect(&GUI::updateGroundTypeScale, this);

	// Attach widgets to table
	tblPost->Attach( sfg::Label::Create( "Wireframe Mode:" ), sf::Rect<sf::Uint32>( 0, 0, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );
	tblPost->Attach( m_wireframeCheck, sf::Rect<sf::Uint32>( 0, 8, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );

	tblPost->Attach( sfg::Label::Create( "Toon Shaded Mode:" ), sf::Rect<sf::Uint32>( 0, 16, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );
	tblPost->Attach( m_toonCheck, sf::Rect<sf::Uint32>( 0, 24, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );

	tblPost->Attach( sfg::Label::Create( "Ground Type Scale:" ), sf::Rect<sf::Uint32>( 0, 32, 5, 1 ), sfg::Table::FILL, sfg::Table::FILL );
	tblPost->Attach( m_groundTypeScale, sf::Rect<sf::Uint32>( 0, 40, 5, 2 ), sfg::Table::FILL, sfg::Table::FILL );

	return tblPost;
}

void GUI::resize() {
	
}