#include <ME.h>

const ME::Vector2f groundPos = { 0, -400 };
const ME::Vector2f groundDim = { 1400, 50 };
const float gravity = 9.81f;

class GroundController : public ME::ScriptComponent
{
	using ME::ScriptComponent::ScriptComponent;

	const float moveSpeed = 5;

	ME::Transform transform;

	void Start()
	{
		using namespace ME;

		transform = GetComponent<Transform>();
		transform.SetPosition({ 0, -300 });
		transform.SetScale({ 1000, 50 });

		SpriteRenderer sprite = AddComponent<SpriteRenderer>();
		sprite.SetColour({ 255, 0, 0, 255 });

		RectangleCollider collider = AddComponent<RectangleCollider>();
		collider.SetWidth(1000);
		collider.SetHeight(50);

		Rigidbody body = AddComponent<Rigidbody>();
		body.SetStatic(true);
		body.SetMass(2);
		body.SetRestitution(0);
	}
};

class SimulationController : public ME::ScriptComponent
{
	using ME::ScriptComponent::ScriptComponent;

	void Update()
	{
		using namespace ME;

		if (Engine::GetMouseDown(0))
		{
			CreateCircleBody(Engine::GetWorldMousePosition(), 14, 1);
		}
	}

	void CreateCircleBody(const ME::Vector2f pos, const float radius, const float mass)
	{
		using namespace ME;

		Rigidbody body = Engine::AddEntity().AddComponent<Rigidbody>();
		body.GetComponent<Transform>().SetPosition(pos);
		body.AddComponent<CircleRenderer>().SetRadius(radius);
		body.AddComponent<CircleCollider>().SetRadius(radius);

		body.SetGravityScale(gravity * 4);
		body.SetMass(mass);
		body.SetRestitution(0.8f);
	}
};

int main(int argc, char* args[])
{
	using namespace ME;

	srand(time(0));

	Engine::Init("Physics_Sim", 1400, 900);

	Engine::AddEntity().AddScript<SimulationController>();

	Engine::AddEntity().AddScript<GroundController>();

	Engine::Start();

	return 0;
}