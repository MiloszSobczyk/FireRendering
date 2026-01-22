#include "BezierCube.h"

#include "Core/App.h"
#include "Managers/ShaderManager.h"

void BezierCube::ResetCube()
{
	float a_2 = edgeLength / 2.0f;
	float a_3 = edgeLength / 3.0f;

	int n = 0;
	for (int i = 0; i < 4; ++i) 
	{
		for (int j = 0; j < 4; ++j) 
		{
			for (int k = 0; k < 4; ++k) 
			{
				cubePoints[n] = glm::vec3(
					-a_2 + k * a_3,
					+a_2 - j * a_3,
					+a_2 - i * a_3
				);

				++n; // 16 * i + 4 * j + k
			}
		}
	}

	// Springs rest length
	float da = glm::sqrt(2.0f) * a_3;

	for (int j = 0; j < 4; ++j) 
	{
		for (int i = 0; i < 16; ++i)
		{
			int I = i + 16 * j;
			// To points on the same layer

			if (i % 4 != 0) 
			{
				// left 
				springsRestLengths[I][I - 1] = a_3;

				// diagonal
				if (i - 4 >= 0) 
				{
					springsRestLengths[I - 1][I - 4] = da;
				}

				// left -> up
				if (i - 5 >= 0) {
					springsRestLengths[I][I - 5] = da;
				}
			}

			// up
			if (i - 4 >= 0) {
				springsRestLengths[I][I - 4] = a_3;
			}

			// To points on the previous layer 
			if (I - 16 >= 0)
			{
				// front 
				springsRestLengths[I][I - 16] = a_3;

				// front -> left
				if (i % 4 != 0) 
				{
					springsRestLengths[I][I - 16 - 1] = da;
				}

				// front -> right
				if (i % 4 != 3) 
				{
					springsRestLengths[I][I - 16 + 1] = da;
				}

				// front -> up
				if (i - 4 >= 0) 
				{
					springsRestLengths[I][I - 16 - 4] = da;
				}

				// front -> down
				if (i + 4 < 16) 
				{
					springsRestLengths[I][I - 16 + 4] = da;
				}
			}

		}
	}

	UpdateCubeRenderer();
	UpdateLongSpringsRenderer();
	UpdateShortSpringsRenderer();
}

void BezierCube::ResetFrame()
{
	float a_2 = edgeLength / 2.0f;

	int n = 0;
	for (int i = 0; i < 2; ++i) 
	{
		for (int j = 0; j < 2; ++j) 
		{
			for (int k = 0; k < 2; ++k) 
			{
				framePoints[n] = glm::vec3(
					-a_2 + k * edgeLength,
					+a_2 - j * edgeLength,
					+a_2 - i * edgeLength
				);
				++n;
			}
		}
	}

	originalFramePoints = framePoints;

	localFrameOffset = glm::vec3(0.f);
	rotationAngles = glm::vec3(0.f);
	lastOffset = localFrameOffset;
	lastRotation = rotationAngles;

	UpdateControlFrameRenderer();
}

void BezierCube::UpdateCubeRenderer()
{
	std::vector<PositionVertexData> vertices;
	vertices.reserve(64);

	for (auto& p : cubePoints)
	{
		vertices.push_back(
			{
				{ p.x, p.y, p.z, 1.f }
			});
	}

	auto indices = GetBezierPatchesIndices();

	cubeRenderer.SetVertices(vertices);
	cubeRenderer.SetIndices(indices);

	for (int i = 0; i < 64; ++i)
	{
		points[i]->GetTranslationComponent()->SetTranslation(glm::vec4(cubePoints[i], 1.f));
	}
}

void BezierCube::UpdateControlFrameRenderer()
{
	std::vector<PositionVertexData> vertices;
	vertices.reserve(8);

	for (auto& p : framePoints)
	{
		vertices.push_back(
			{
				{ p.x, p.y, p.z, 1.f }
			});
	}

	std::vector<unsigned int> indices = {
		0, 1, 0, 2, 1, 3, 2, 3,
		4, 5, 4, 6, 5, 7, 6, 7,
		0, 4, 1, 5, 2, 6, 3, 7
	};

	controlFrameRenderer.SetVertices(vertices);
	controlFrameRenderer.SetIndices(indices);
}

void BezierCube::UpdateShortSpringsRenderer()
{
	std::vector<PositionVertexData> vertices;
	vertices.reserve(64);

	for (auto& p : cubePoints)
	{
		vertices.push_back
		(
			{
				{ p.x, p.y, p.z, 1.f }
			}
		);
	}

	auto indices = GetShortSpringsIndices();

	for (auto& p : frameSprings)
	{
		vertices.push_back({ glm::vec4{framePoints[p.first], 1.f} });
		vertices.push_back({ glm::vec4{cubePoints[p.second], 1.f} });
		indices.push_back(vertices.size() - 2);
		indices.push_back(vertices.size() - 1);
	}

	shortSpringsRenderer.SetVertices(vertices);
	shortSpringsRenderer.SetIndices(indices);
}

void BezierCube::UpdateLongSpringsRenderer()
{
	std::vector<PositionVertexData> vertices;
	vertices.reserve(64);

	for (auto& p : cubePoints)
	{
		vertices.push_back
		(
			{
				{ p.x, p.y, p.z, 1.f }
			}
		);
	}

	auto indices = GetLongSpringsIndices();

	longSpringsRenderer.SetVertices(vertices);
	longSpringsRenderer.SetIndices(indices);
}

std::vector<unsigned int> BezierCube::GetBezierPatchesIndices()
{
	return {
		// front
		 0,  1,  2,  3,
		 4,  5,  6,  7,
		 8,  9, 10, 11,
		12, 13, 14, 15,

		// back
		60, 61, 62, 63,
		56, 57, 58, 59,
		52, 53, 54, 55,
		48, 49, 50, 51,

		// right 
		 3, 19, 35, 51,
		 7, 23, 39, 55,
		11, 27, 43, 59,
		15, 31, 47, 63,

		// left 
		12, 28, 44, 60,
		 8, 24, 40, 56,
		 4, 20, 36, 52,
		 0, 16, 32, 48,

		 // top
		48, 49, 50, 51,
		32, 33, 34, 35,
		16, 17, 18, 19,
		0,  1,  2,  3,

		// bottom 
		12, 13, 14, 15,
		28, 29, 30, 31,
		44, 45, 46, 47,
		60, 61, 62, 63
	};
}

std::vector<unsigned int> BezierCube::GetShortSpringsIndices()
{
	std::vector<unsigned int> indices;
	indices.reserve(64 * 6);

	float a_3 = edgeLength / 3.0f;

	for (int j = 0; j < 4; ++j)
	{
		for (int i = 0; i < 16; ++i)
		{
			int I = i + j * 16;

			if (i % 4 != 0)
			{
				indices.push_back(I);
				indices.push_back(I - 1);
			}

			if (i - 4 >= 0)
			{
				indices.push_back(I);
				indices.push_back(I - 4);
			}

			if (I - 16 >= 0)
			{
				indices.push_back(I);
				indices.push_back(I - 16);
			}
		}
	}

	return indices;
}

std::vector<unsigned int> BezierCube::GetLongSpringsIndices()
{
	std::vector<unsigned int> indices;
	indices.reserve(64 * 12);

	for (int j = 0; j < 4; ++j)
	{
		for (int i = 0; i < 16; ++i)
		{
			int I = i + j * 16;

			if (i % 4 != 0 && i - 4 >= 0)
			{
				indices.push_back(I);
				indices.push_back(I - 5);
			}

			if (i % 4 != 3 && i - 4 >= 0)
			{
				indices.push_back(I);
				indices.push_back(I - 3);
			}

			if (I - 16 >= 0)
			{
				if (i % 4 != 0)
				{
					indices.push_back(I);
					indices.push_back(I - 16 - 1);
				}

				if (i % 4 != 3)
				{
					indices.push_back(I);
					indices.push_back(I - 16 + 1);
				}

				if (i - 4 >= 0)
				{
					indices.push_back(I);
					indices.push_back(I - 16 - 4);
				}

				if (i + 4 < 16)
				{
					indices.push_back(I);
					indices.push_back(I - 16 + 4);
				}
			}
		}
	}

	return indices;
}

void BezierCube::RenderControlFrameUI()
{
	glm::vec3 frameCenter(0.f);
	for (auto& p : originalFramePoints)
	{
		frameCenter += p;
	}
	frameCenter /= static_cast<float>(originalFramePoints.size());

	ImGui::DragFloat3("Control Frame Position", &localFrameOffset.x, 0.1f, -3.0f, 3.0f, "%.2f");

	ImGui::DragFloat3("Control Frame Rotation (deg)", &rotationAngles.x, 1.0f, -180.f, 180.f, "%.1f");

	if (localFrameOffset != lastOffset || rotationAngles != lastRotation)
	{
		glm::vec3 radians = glm::radians(rotationAngles);

		glm::mat4 rotX = glm::rotate(glm::mat4(1.f), radians.x, glm::vec3(1.f, 0.f, 0.f));
		glm::mat4 rotY = glm::rotate(glm::mat4(1.f), radians.y, glm::vec3(0.f, 1.f, 0.f));
		glm::mat4 rotZ = glm::rotate(glm::mat4(1.f), radians.z, glm::vec3(0.f, 0.f, 1.f));

		glm::mat4 rotationMatrix = rotZ * rotY * rotX;

		for (int i = 0; i < framePoints.size(); ++i)
		{
			glm::vec4 localPos = glm::vec4(originalFramePoints[i] - frameCenter, 1.f);
			localPos = rotationMatrix * localPos;
			framePoints[i] = glm::vec3(localPos) + frameCenter + localFrameOffset;
		}

		UpdateControlFrameRenderer();

		lastOffset = localFrameOffset;
		lastRotation = rotationAngles;
	}
}

void BezierCube::RenderPointsUI()
{
	if (ImGui::BeginCombo("Select Point", std::to_string(selectedPoint).c_str()))
	{
		for (int i = 0; i < 64; ++i)
		{
			if (i % 16 == 0 && i != 0)
			{
				ImGui::Separator();
			}

			bool isSelected = (selectedPoint == i);

			if (ImGui::Selectable(std::to_string(i).c_str(), isSelected))
			{
				selectedPoint = i;
			}

			if (isSelected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}

		ImGui::EndCombo();
	}

	glm::vec3& p = cubePoints[selectedPoint];
	glm::vec3 editable = p;

	if (ImGui::DragFloat3("Position", &editable.x, 0.01f))
	{
		p = editable;

		points[selectedPoint]->GetTranslationComponent()->SetTranslation(
			glm::vec4(p, 1.f)
		);

		UpdateCubeRenderer();
		UpdateShortSpringsRenderer();
		UpdateLongSpringsRenderer();
	}
}

void BezierCube::ApplyPointHighlighting()
{
	for (int i = 0; i < 64; ++i)
	{
		if (!useControlFrame && i == selectedPoint)
		{
			points[i]->SetColor(glm::vec4(1.f, 1.f, 0.f, 1.f));
		}
		else
		{
			points[i]->SetColor(glm::vec4(0.f, 0.f, 0.f, 1.f));
		}
	}
}

BezierCube::BezierCube(float inEdgeLength)
	: edgeLength(inEdgeLength), 
	cubeRenderer(VertexDataType::PositionVertexData),
	controlFrameRenderer(VertexDataType::PositionVertexData),
	shortSpringsRenderer(VertexDataType::PositionVertexData),
	longSpringsRenderer(VertexDataType::PositionVertexData)
{
	frameSprings[0] = 0;
	frameSprings[1] = 3;
	frameSprings[2] = 12;
	frameSprings[3] = 15;

	frameSprings[4] = 48;
	frameSprings[5] = 51;
	frameSprings[6] = 60;
	frameSprings[7] = 63;

	for (int i = 0; i < 64; ++i)
	{
		points[i] = std::make_shared<Cube>(false, false, false);
		points[i]->GetScalingComponent()->SetScaling(glm::vec3(0.04f));
		points[i]->SetColor(glm::vec4(0.f, 0.f, 0.f, 1.f));
	}
	
	Reset();
}

void BezierCube::Render()
{
	ApplyPointHighlighting();

	auto shader = ShaderManager::GetInstance().GetShader(ShaderName::BezierPatch);
	if (drawCube)
	{
		cubeRenderer.SetPatchParameters(16);

		shader->Bind();
		shader->SetUniformVec4f("u_color", ColorPalette::Get(Color::Green));
		shader->SetUniformFloat("u_tessellationLevel", 16);
		shader->SetUniformMat4f("u_viewMatrix", App::GetViewMatrix());
		shader->SetUniformMat4f("u_projectionMatrix", App::GetProjectionMatrix());

		cubeRenderer.Render(GL_PATCHES);

	}
	shader->Unbind();

	if (useControlFrame)
	{
		shader = ShaderManager::GetInstance().GetShader(ShaderName::Default);

		shader->Bind();
		shader->SetUniformVec4f("u_color", ColorPalette::Get(Color::Blue));
		shader->SetUniformMat4f("u_viewMatrix", App::GetViewMatrix());
		shader->SetUniformMat4f("u_projectionMatrix", App::GetProjectionMatrix());
		shader->SetUniformMat4f("u_modelMatrix", GetModelMatrix());


		controlFrameRenderer.Render(GL_LINES);

		shader->Unbind();
	}

	glLineWidth(3.0f);
	if (drawShortSprings)
	{
		shader = ShaderManager::GetInstance().GetShader(ShaderName::Default);

		shader->Bind();
		shader->SetUniformVec4f("u_color", ColorPalette::Get(Color::Red));
		shader->SetUniformMat4f("u_viewMatrix", App::GetViewMatrix());
		shader->SetUniformMat4f("u_projectionMatrix", App::GetProjectionMatrix());
		shader->SetUniformMat4f("u_modelMatrix", GetModelMatrix());

		shortSpringsRenderer.Render(GL_LINES);

		shader->Unbind();
	}

	if (drawLongSprings)
	{
		shader = ShaderManager::GetInstance().GetShader(ShaderName::Default);

		shader->Bind();
		shader->SetUniformVec4f("u_color", ColorPalette::Get(Color::Black));
		shader->SetUniformMat4f("u_viewMatrix", App::GetViewMatrix());
		shader->SetUniformMat4f("u_projectionMatrix", App::GetProjectionMatrix());
		shader->SetUniformMat4f("u_modelMatrix", GetModelMatrix());

		longSpringsRenderer.Render(GL_LINES);

		shader->Unbind();
	}
	glLineWidth(1.0f);

	if (drawPoints)
	{
		for (auto point : points)
		{
			point->Render();
		}
	}
}

void BezierCube::RenderUI()
{
	ImGui::Checkbox("Draw Cube", &drawCube);
	ImGui::Checkbox("Draw Short Springs", &drawShortSprings);
	ImGui::Checkbox("Draw Long Springs", &drawLongSprings);
	ImGui::Checkbox("Draw Points", &drawPoints);

	ImGui::SeparatorText("Controls");
	ImGui::Checkbox("Use Control Frame", &useControlFrame);

	if (useControlFrame)
	{
		RenderControlFrameUI();
	}
	else
	{
		RenderPointsUI();
	}
}

void BezierCube::Reset(float inEdgeLength)
{
	edgeLength = inEdgeLength;
	ResetCube();
	ResetFrame();
}

void BezierCube::SetEdgeLength(float inEdgeLength)
{
	edgeLength = inEdgeLength;
}

void BezierCube::SetCubePoints(std::array<glm::vec3, 64> inCubePoints)
{
	cubePoints = inCubePoints;
	UpdateCubeRenderer();
	UpdateShortSpringsRenderer();
	UpdateLongSpringsRenderer();
}

void BezierCube::SetFramePoints(std::array<glm::vec3, 8> inFramePoints)
{
	framePoints = inFramePoints;
}
