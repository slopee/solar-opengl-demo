struct GLFWwindow;

class DebugSystem
{
public:
	void Init(GLFWwindow* window, const char* glsl_version);
	void End();

    void Render();
};
