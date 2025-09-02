{
  description = "Daedalus - RP2350 firmware and Vim plugin";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs =
    {
      nixpkgs,
      flake-utils,
      ...
    }:
    flake-utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = import nixpkgs {
          inherit system;
        };

        # Needs to be synced past
        # https://github.com/NixOS/nixpkgs/pull/321786
        local-pico-sdk = pkgs.pico-sdk.override {
          withSubmodules = true;
        };
      in
      {
        devShells.default = pkgs.mkShell {
          buildInputs = with pkgs; [
            # C/C++ development
            gcc
            gcc-arm-embedded
            cmake
            gnumake

            # Pico SDK dependencies
            git
            python3
            python3Packages.pip
            python3Packages.setuptools
            picotool

            # Debugging tools
            gdb
            openocd

            # Utilities
            pkg-config
            minicom

            # Code quality
            clang-tools # clang-format, clang-tidy
            cppcheck
          ];

          shellHook = ''
            # Set environment variables
            export PICO_SDK_PATH="${local-pico-sdk}/lib/pico-sdk"

            echo "Daedalus development environment ready!"
          '';
        };
      }
    );
}
