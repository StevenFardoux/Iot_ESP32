<!-- Improved compatibility of back to top link -->
<a id="readme-top"></a>

<!-- PROJECT SHIELDS -->
[![LinkedIn][linkedin-shield]][linkedin-url]

<!-- PROJECT LOGO -->
<div align="center">
  <h1 align="center">IoT ESP32 Project</h1>

  <p align="center">
    A training project on IoT solutions using ESP32-C3 with GPS and 4G capabilities
    <br />
    <a href="#about-the-project"><strong>Explore the docs »</strong></a>
  </p>
</div>

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->
## About The Project

This project explores IoT solutions using a modified ESP32-C3 development board. The board integrates:

* GPS (GNSS) chip for location tracking
* 4G module (CATM1) for cellular connectivity

The main objectives were:
* Learn about IoT systems architecture
* Implement GPS location tracking
* Set up cellular communication
* Send data to a TCP server

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Built With

* [![C++][C++]][C++-url]
* [![PlatformIO][PlatformIO]][PlatformIO-url]
* [![Arduino][Arduino]][Arduino-url]
* [![ESP32][ESP32]][ESP32-url]
* [![SIM7080G][SIM7080G]][SIM7080G-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- GETTING STARTED -->
## Getting Started

To get started with this project, you'll need the following:

### Prerequisites

* PlatformIO IDE (VSCode extension)
* ESP32-C3 development board with SIM7080G module
* Active SIM card for cellular connectivity

### Installation

1. Clone the repository
   ```sh
   git clone https://github.com/StevenFardoux/Iot_ESP32.git
   ```
2. Connect the hardware:
   - Connect GPS antenna to the GPS port
   - Insert SIM card into the SIM slot
   - Connect ESP32 board via USB
3. Build and upload to your ESP32:
   ```sh
   platformio run -t upload
   ```
4. Monitor the serial output:
   ```sh
   platformio device monitor -b 115200
   ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>

[C++]: https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white
[C++-url]: https://isocpp.org/
[PlatformIO]: https://img.shields.io/badge/PlatformIO-FF6F00?style=for-the-badge&logo=platformio&logoColor=white
[PlatformIO-url]: https://platformio.org/
[Arduino]: https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white
[Arduino-url]: https://www.arduino.cc/
[ESP32]: https://img.shields.io/badge/ESP32-E7352C?style=for-the-badge&logo=espressif&logoColor=white
[ESP32-url]: https://www.espressif.com/
[SIM7080G]: https://img.shields.io/badge/SIM7080G-2C3E50?style=for-the-badge
[SIM7080G-url]: https://www.simcom.com/product/SIM7080G.html
[linkedin-shield]: https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white
[linkedin-url]: https://www.linkedin.com/in/steven-fardoux-dev/