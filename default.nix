with import <nixpkgs> {};

stdenv.mkDerivation {
  name = "sdl-sample";
  src = ./src;
  buildInputs = [ 
    clang 
    SDL2 
    SDL2.dev 
    vulkan-headers 
    vulkan-loader 
    vulkan-tools 
    mesa
    vulkan-validation-layers
    vulkan-extension-layer
  ];
  buildPhase = "clang++ -std=c++23 -o main main.cpp -lSDL2 -lvulkan";

  installPhase = ''
    mkdir -p $out/bin
    cp main $out/bin/
    '';
}

