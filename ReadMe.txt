========================================================================
  Volumetric Voxel Renderer
========================================================================

A volumetric voxel renderer that implements Beer's Law.

The renderer performs a raymarch through the voxel grid for each pixel to accumulate the density and light transmittance values and calculates the appropriate color. The density values for the voxel grid can be either read in explicitly from a plain text file or generated given a configuration file that lists the desired shapes to be rendered.

Using GLM and EasyBMP libraries to aid with linear algebra operations and BMP creation.