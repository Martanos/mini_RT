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

3. Render
4. Utils

Important notes:
- AA is enabled by default.
- Max recursion depth is hard set to 30.
- Initial window size is 800x600 but can adapt to window changes. Just keep in mind that the aspect ratio is not maintained and normals are not adjusted.
- All lights are spotlights and direction is currently just straig
