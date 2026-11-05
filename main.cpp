#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

#include <iostream>

char MachineName[128] = "Explorer 01";
double mass;
double length;
double width;
double height;
double CentreOfMassX;
double CentreOfMassY;
double CentreOfMassZ;
double MaxPayload;
int NumberOfWheels;
int NumberOfMotors;

double MaxSpeed;
double MaxAcceleration;
double MaxDeceleration;
double MaxTurningRate;
double MinTurningRadius;
double MaxClimbingAngle;
double MaxDescendingAngle;
double MaxObstacleHeight;
double MaxOperatingDistance;
double BrakingForce;

double MotorPower;
double MaxMotorTorque;
double MaxMotorRPM;
double MotorEfficiency;
double MotorMass;
double WheelRadius;
double GearRatio;

double BatteryVoltage;
double BatteryCapacity;
double BatteryEnergy;
double MaxCurrent;
double AveragePowerConsumption;
double MaxPowerConsumption;
double BatteryMass;
double SolarPanelPower;
double MinOperatingTemperature;
double MaxOperatingTemperature;

double FrictionCoefficient;
int WheelMaterial;
double WheelWidth;
double SuspensionStiffness;
double SuspensionDamping;
double GroundClearance;
double MaxGroundPressure;
double SuspensionTravel;

double GPSAccuracy;
int CameraWidth;
int CameraHeight;
double LidarRange;
double RadarRange;
double UltrasonicRange;
double IMUAccuracy;
double CommunicationRange;
double ControlFrequency;
double SensorFrequency;

double StartX;
double StartY;
double StartZ;
double StartRoll;
double StartPitch;
double StartYaw;
double StartBatteryCharge;
double StartVelocity;
double StartTemperature;
double InitialPayload;

bool inSimulation = false;

int main() {

    if (!glfwInit()) {
        std::cerr << "Failed to initialise GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(
        1920, 1080,
        "MarsCos Simulation",
        nullptr, nullptr
    );

    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialise GLAD\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();

    io.FontGlobalScale = 1.25f;

    ImGui::StyleColorsDark();

    ImGui::GetStyle().ScaleAllSizes(1.15f);

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glClearColor(0.05f, 0.07f, 0.10f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui::SetNextWindowPos(
            ImVec2(60.0f, 40.0f),
            ImGuiCond_Always
        );

        ImGui::SetNextWindowSize(
            ImVec2(1800.0f, 980.0f),
            ImGuiCond_Always
        );

        ImGui::Begin(
            "MarsCos Simulation 2000",
            nullptr,
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoCollapse
        );

        ImGui::Text("MarsCos - Robot Configuration and Simulation");
        ImGui::Separator();

        if (ImGui::Button("Simulate", ImVec2(250, 50))) {
            inSimulation = true;
        }
        ImGui::Separator();

        if (ImGui::BeginTabBar("ConfigurationTabs")) {

            if (ImGui::BeginTabItem("General")) {
                ImGui::SeparatorText("Physical Specifications");
                ImGui::InputText(
                    "Machine Name",
                    MachineName,
                    IM_ARRAYSIZE(MachineName)
                );
                ImGui::InputDouble("Mass (kg)", &mass);
                ImGui::InputDouble("Length (m)", &length);
                ImGui::InputDouble("Width (m)", &width);
                ImGui::InputDouble("Height (m)", &height);
                ImGui::SeparatorText("Centre of Mass");
                ImGui::InputDouble("Centre of Mass X (m)", &CentreOfMassX);
                ImGui::InputDouble("Centre of Mass Y (m)", &CentreOfMassY);
                ImGui::InputDouble("Centre of Mass Z (m)", &CentreOfMassZ);
                ImGui::SeparatorText("Payload and Hardware");
                ImGui::InputDouble("Maximum Payload (kg)", &MaxPayload);
                ImGui::InputInt("Number of Wheels", &NumberOfWheels);
                ImGui::InputInt("Number of Motors", &NumberOfMotors);

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Movement")) {
                ImGui::SeparatorText("Speed and Acceleration");
                ImGui::InputDouble("Maximum Speed (m/s)", &MaxSpeed);
                ImGui::InputDouble("Maximum Acceleration (m/s^2)", &MaxAcceleration);
                ImGui::InputDouble("Maximum Deceleration (m/s^2)", &MaxDeceleration);
                ImGui::InputDouble("Maximum Turning Rate (deg/s)", &MaxTurningRate);
                ImGui::InputDouble("Minimum Turning Radius (m)", &MinTurningRadius);
                ImGui::SeparatorText("Terrain Capabilities");
                ImGui::InputDouble("Maximum Climbing Angle (degrees)", &MaxClimbingAngle);
                ImGui::InputDouble("Maximum Descending Angle (degrees)", &MaxDescendingAngle);
                ImGui::InputDouble("Maximum Obstacle Height (m)", &MaxObstacleHeight);
                ImGui::InputDouble("Maximum Operating Distance (m)", &MaxOperatingDistance);
                ImGui::InputDouble("Braking Force (N)", &BrakingForce);

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Motors")) {
                ImGui::SeparatorText("Motor Performance");
                ImGui::InputDouble("Motor Power (W)", &MotorPower);
                ImGui::InputDouble("Maximum Motor Torque (Nm)", &MaxMotorTorque);
                ImGui::InputDouble("Maximum Motor RPM", &MaxMotorRPM);
                ImGui::InputDouble("Motor Efficiency (%)", &MotorEfficiency);
                ImGui::InputDouble("Motor Mass (kg)", &MotorMass);
                ImGui::SeparatorText("Wheel and Gear System");
                ImGui::InputDouble("Wheel Radius (m)", &WheelRadius);
                ImGui::InputDouble("Gear Ratio", &GearRatio);

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Electrical")) {
                ImGui::SeparatorText("Battery");
                ImGui::InputDouble("Battery Voltage (V)", &BatteryVoltage);
                ImGui::InputDouble("Battery Capacity (Ah)", &BatteryCapacity);
                ImGui::InputDouble("Battery Energy (Wh)", &BatteryEnergy);
                ImGui::InputDouble("Maximum Current (A)", &MaxCurrent);
                ImGui::InputDouble("Battery Mass (kg)", &BatteryMass);
                ImGui::SeparatorText("Power Consumption");
                ImGui::InputDouble("Average Power Consumption (W)", &AveragePowerConsumption);
                ImGui::InputDouble("Maximum Power Consumption (W)", &MaxPowerConsumption);
                ImGui::InputDouble("Solar Panel Power (W)", &SolarPanelPower);
                ImGui::SeparatorText("Operating Temperature");
                ImGui::InputDouble("Minimum Operating Temperature (C)", &MinOperatingTemperature);
                ImGui::InputDouble("Maximum Operating Temperature (C)", &MaxOperatingTemperature);

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Mechanical")) {
                ImGui::SeparatorText("Wheel Properties");
                ImGui::InputDouble("Friction Coefficient", &FrictionCoefficient);
                ImGui::InputInt("Wheel Material", &WheelMaterial);
                ImGui::InputDouble("Wheel Width (m)", &WheelWidth);
                ImGui::SeparatorText("Suspension");
                ImGui::InputDouble("Suspension Stiffness (N/m)", &SuspensionStiffness);
                ImGui::InputDouble("Suspension Damping (Ns/m)", &SuspensionDamping);
                ImGui::InputDouble("Suspension Travel (m)", &SuspensionTravel);
                ImGui::SeparatorText("Ground Interaction");
                ImGui::InputDouble("Ground Clearance (m)", &GroundClearance);
                ImGui::InputDouble("Maximum Ground Pressure (Pa)", &MaxGroundPressure);

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Sensors")) {
                ImGui::SeparatorText("Navigation");
                ImGui::InputDouble("GPS Accuracy (m)", &GPSAccuracy);
                ImGui::InputDouble("Communication Range (m)", &CommunicationRange);
                ImGui::SeparatorText("Camera");
                ImGui::InputInt("Camera Width (pixels)", &CameraWidth);
                ImGui::InputInt("Camera Height (pixels)", &CameraHeight);
                ImGui::SeparatorText("Detection Systems");
                ImGui::InputDouble("LiDAR Range (m)", &LidarRange);
                ImGui::InputDouble("Radar Range (m)", &RadarRange);
                ImGui::InputDouble("Ultrasonic Range (m)", &UltrasonicRange);
                ImGui::SeparatorText("Control and Measurement");
                ImGui::InputDouble("IMU Accuracy (degrees)", &IMUAccuracy);
                ImGui::InputDouble("Control Frequency (Hz)", &ControlFrequency);
                ImGui::InputDouble("Sensor Frequency (Hz)", &SensorFrequency);

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Starting Conditions")) {
                ImGui::SeparatorText("Starting Position");
                ImGui::InputDouble("Starting X (m)", &StartX);
                ImGui::InputDouble("Starting Y (m)", &StartY);
                ImGui::InputDouble("Starting Z (m)", &StartZ);
                ImGui::SeparatorText("Starting Orientation");
                ImGui::InputDouble("Starting Roll (degrees)", &StartRoll);
                ImGui::InputDouble("Starting Pitch (degrees)", &StartPitch);
                ImGui::InputDouble("Starting Yaw (degrees)", &StartYaw);
                ImGui::SeparatorText("Starting State");
                ImGui::InputDouble("Starting Battery Charge (%)", &StartBatteryCharge);
                ImGui::InputDouble("Starting Velocity (m/s)", &StartVelocity);
                ImGui::InputDouble("Starting Temperature (C)", &StartTemperature);
                ImGui::InputDouble("Initial Payload (kg)", &InitialPayload);

                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }
        ImGui::End();

        ImGui::Render();

        int displayWidth, displayHeight;
        glfwGetFramebufferSize(window, &displayWidth, &displayHeight);
        glViewport(0, 0, displayWidth, displayHeight);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}