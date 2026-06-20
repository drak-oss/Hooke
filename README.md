# Hooke — Graph-Based Spring Simulation System
Hooke is an interactive graph-based spring simulation engine built in C++ using SDL2 and GLAD for rendering and Dear ImGui for the user interface.

The system models spring networks as a graph where nodes represent physical objects and edges represent springs. It supports two types of nodes:

Hook Nodes — Fixed anchor points that remain stationary during simulation.
Dynamic Nodes — Movable objects whose positions evolve according to the forces acting on them.

Nodes can be connected through one or more springs, allowing users to construct and simulate a wide variety of mechanical systems. During each simulation step, spring forces are computed using Hooke's Law and applied across the graph, producing realistic motion and oscillatory behavior.

Key features include:

Interactive creation and editing of spring networks
Support for multiple anchors, masses, and interconnected spring systems
Real-time physics simulation and visualization
Graph-based architecture for flexible system modeling
Immediate-mode GUI controls powered by Dear ImGui
Customizable spring and node parameters

Hooke demonstrates how complex spring-mass systems can be represented and simulated through graph structures, making it a useful tool for exploring physics concepts, constraint-based systems, and numerical simulation techniques.
