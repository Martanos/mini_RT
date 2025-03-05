Structural overview of the code.

1. Parsing
    - Parses the scene file and creates the scene struct
    - Parses the camera data and creates the camera struct
    - Parses the light data and creates the light struct
    - Parses the object data and creates the object struct

2. Object prep
    - Objective for this section is to prepare "static" values ie (Normalized view port dimensions)
    Flow:
        ft_object_prep_main()
            - ft_cam_prep()
            - ft_light_prep()
            - ft_obj_prep()

3. Primary Ray Generation
   - Calculate camera ray direction for each pixel
   - Apply camera transformation matrix

4. Intersection Testing
   - Test ray against all objects in scene
   - Find closest intersection point
   - Store intersection information (point, normal, material)

5. Material Property Gathering
   - Get base material color
   - Get texture coordinates at intersection point
   - Apply checkerboard pattern if specified
   - Sample bump/normal maps if present

6. Normal Calculation
   - Get geometric normal at intersection point
   - If bump map exists, perturb normal using height differences
   - If normal map exists, transform sampled normal to world space
   - Normalize final normal vector

7. Lighting Calculation (Phong Model)
   - For each light source:
     - Calculate light direction vector
     - Check for shadows (cast shadow ray)
     - Calculate diffuse component (Lambert's law)
     - Calculate specular component (Phong reflection)
     - Apply light attenuation based on distance
     - Accumulate light contributions

8. Specular Reflection
   - Calculate reflection direction using incident ray and surface normal
   - Cast reflection ray recursively (with depth limit)
   - Blend reflection color with local color based on material reflectivity

9. Texture Application
   - Map 3D intersection point to 2D texture coordinates
   - For checkerboard:
     - Scale and offset coordinates
     - Determine pattern color based on position
   - For image textures:
     - Sample texture at mapped coordinates
     - Apply texture filtering if needed

10. Final Color Composition
    - Combine all lighting components
    - Apply global illumination effects
    - Clamp final color values
    - Write to output buffer

11. Render
    - Renders the scene
    - Puts the final color to the screen

Important notes:
- AA is enabled by default.
- Max recursion depth is hard set to 30.
- Initial window size is 800x600 but can adapt to window changes. Just keep in mind that the aspect ratio is not maintained and normals are not adjusted.
- All lights are spotlights and direction is currently just straight up.
