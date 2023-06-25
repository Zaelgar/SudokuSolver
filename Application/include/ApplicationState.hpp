// Jaidon van Herwaarden June 2023

class Application;

class ApplicationState
{
public:

	virtual void Initialize(const Application* const application) = 0;
	virtual void Terminate() = 0;

	virtual bool Update() = 0;
	virtual void Render() = 0;
};