#include "core.hpp"

using namespace rack;



struct NotesWidget : ModuleWidget {
	TextField *textField;

	NotesWidget(Module *module) : ModuleWidget(module) {
		box.size = Vec(RACK_GRID_WIDTH * 18, RACK_GRID_HEIGHT);

		{
			Panel *panel = new LightPanel();
			panel->box.size = box.size;
			addChild(panel);
		}

		addChild(Widget::create<ScrewSilver>(Vec(15, 0)));
		addChild(Widget::create<ScrewSilver>(Vec(15, 365)));
		addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 30, 0)));
		addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 30, 365)));

		textField = new TextField();
		textField->box.pos = Vec(15, 15);
		textField->box.size = box.size.minus(Vec(30, 30));
		textField->multiline = true;
		addChild(textField);
	}

	json_t *toJson() override {
		json_t *rootJ = ModuleWidget::toJson();

		// text
		json_object_set_new(rootJ, "text", json_string(textField->text.c_str()));

		return rootJ;
	}

	void fromJson(json_t *rootJ) override {
		ModuleWidget::fromJson(rootJ);

		// text
		json_t *textJ = json_object_get(rootJ, "text");
		if (textJ)
			textField->text = json_string_value(textJ);
	}
};


Model *modelNotes = Model::create<Module, NotesWidget>("Core", "Notes", "Notes", BLANK_TAG);
