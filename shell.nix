{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    SDL2
    SDL2.dev
    clang-tools
    gcc
    vulkan-tools
    vulkan-headers
    vulkan-loader
    vulkan-validation-layers
    vulkan-extension-layer
    vulkan-tools-lunarg
    mesa
  ];
  VK_LAYER_PATH = "${pkgs.vulkan-validation-layers}/share/vulkan/explicit_layer.d";
  XDG_DATA_DIRS = builtins.getEnv "XDG_DATA_DIRS";
  LD_LIBRARY_PATH="${pkgs.glfw}/lib:${pkgs.freetype}/lib:${pkgs.vulkan-loader}/lib:${pkgs.vulkan-validation-layers}/lib";
  shellHook = ''
    lvim
  '';
}
