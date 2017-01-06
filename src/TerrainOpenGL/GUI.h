#ifndef GUI_H
#define GUI_H

#include "Renderer.h"
#include <SFGUI\SFGUI.hpp>

class GUI {
public:
	GUI(Renderer &renderer);
	~GUI(void);

	void					resize();
	void					reload();
	sfg::Desktop			getDesktop() const { return m_desktop; }

	void					updateNoiseSeed();
	void					updateCornerSeed();
	void					updateTessInner();
	void					updateTessOuter();
	void					updateSmoothing();
	void					updateMountainHeight();

	void					updateWaterScale();
	void					updateRipple();
	void					updateTransparency();
	void					updateWaterRed();
	void					updateWaterGreen();
	void					updateWaterBlue();

	void					updateRadiusScale();
	void					updateLightRed();
	void					updateLightGreen();
	void					updateLightBlue();

	void					updateLight();

	void					updateWireframe();
	void					updateThermal();
	void					updateGroundTypeScale();

	void					importSettings();
	void					exportSettings();
	void					randomise();
	void					generateWorld();

protected:
	sfg::Window::Ptr		initGUIWindow();
	sfg::Window::Ptr		initCommandWindow();
	sfg::Table::Ptr			initTessTable();
	sfg::Table::Ptr			initWaterTable();
	sfg::Table::Ptr			initLightTable();
	sfg::Table::Ptr			initPostTable();

	sfg::Desktop			m_desktop;

	Renderer				&m_renderer;

	// Command pane
	sfg::Button::Ptr		m_generateBtn;
	sfg::Button::Ptr		m_importBtn;
	sfg::Button::Ptr		m_exportBtn;

	// Terrain pane
	sfg::Scale::Ptr			m_tessInnerScale;
	sfg::Scale::Ptr			m_tessOuterScale;
	sfg::Scale::Ptr			m_smoothingScale;
	sfg::Scale::Ptr			m_mountainScale;
	sfg::CheckButton::Ptr	m_thermalCheck;
	sfg::ComboBox::Ptr		m_noiseCombo;
	sfg::Entry::Ptr			m_noiseSeedBox;
	sfg::Entry::Ptr			m_cornerSeedBox;
	sfg::ComboBox::Ptr		m_dataSizeCombo;
	sfg::Image::Ptr			m_heightmapImage;
	sfg::Button::Ptr		m_randomiseBtn;

	// Water pane
	sfg::Scale::Ptr			m_waterScale;
	sfg::Scale::Ptr			m_rippleScale;
	sfg::Scale::Ptr			m_transparencyScale;
	sfg::Scale::Ptr			m_waterRedScale;
	sfg::Scale::Ptr			m_waterGreenScale;
	sfg::Scale::Ptr			m_waterBlueScale;

	// Light pane
	sfg::Scale::Ptr			m_radiusScale;
	sfg::Scale::Ptr			m_lightRedScale;
	sfg::Scale::Ptr			m_lightGreenScale;
	sfg::Scale::Ptr			m_lightBlueScale;

	// Post processing pane
	sfg::CheckButton::Ptr	m_wireframeCheck;
	sfg::CheckButton::Ptr	m_toonCheck;
	sfg::Scale::Ptr			m_groundTypeScale;

};

#endif