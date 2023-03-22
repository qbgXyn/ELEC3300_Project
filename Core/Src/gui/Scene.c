// the top level of gui
// all object is under scene
struct Scene {
	struct Window** window_list;
	enum Scenes {MAIN, SINGLE, MULTIPLE, IN_GAME} scene;

	/*
	    input:    an window

	    output:   none

	    remarks:  This function is called when adding new window into Scene
	*/
	void Add_Window(struct Window* w) {
		//task
	}
};

