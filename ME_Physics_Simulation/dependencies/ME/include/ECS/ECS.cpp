#include "ECS.h"
#include "ScriptComponent.h"

namespace ME
{
	void ECS::StartScript(ScriptComponent& script)
	{
		script.Start();
	}

	bool ECS::CheckScriptID(ScriptComponent& script, const unsigned int id)
	{
		return script.GetEntityID() == id;
	}
}