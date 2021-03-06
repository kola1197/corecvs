project (CoreCVSTests)

set(MODULE_NAME corecvs)


MESSAGE( STATUS "Including GTest on Tests build" )
find_package( GTest REQUIRED)
include_directories (${GTest_INCLUDE_DIR}/..)

set (CORE_TEST_SOURCES
    eigen/main_test_eigen_integration.cpp

    ultrasound/main_test_ultrasound_reconstruction.cpp
    ultrasound/model.cpp
    ultrasound/imgreader.cpp
    ultrasound/model.h
    ultrasound/imgreader.h

    generated/testEnum.h
    generated/testSubClass.h
    generated/testClass.h
    generated/testBlock.h

    generated/testSubClass.cpp
    generated/testClass.cpp
    generated/testBlock.cpp

#    eigen/main_test_eigen.cpp
    affine/main_test_affine.cpp
#    aLowCodec/main_test_aLowCodec.cpp
    arithmetics/main_test_arithmetics.cpp
    assignment/main_test_assignment.cpp
    automotive/main_test_automotive.cpp
    buffer/main_test_buffer.cpp
    cameramodel/main_test_cameramodel.cpp
    cholesky/main_test_cholesky.cpp
    cloud/main_test_cloud.cpp
    color/main_test_color.cpp
    commandline/main_test_commandline.cpp
    convolve/main_test_convolve.cpp
#    cornerdetector/main_test_cornerdetector.cpp
#    debayer/main_test_debayer.cpp
    deform/main_test_deform.cpp
    derivative/main_test_derivative.cpp
    draw/main_test_draw.cpp
    fastkernel/main_test_fastkernel.cpp
    fileformats/main_test_fileformats.cpp
    filesystem/main_test_filesystem.cpp
#    gaussianSolution/main_test_gaussianSolution.cpp      # TODO: check it...
    geometry/main_test_geometry.cpp
    gradient/main_test_gradient.cpp
    histogram/main_test_histogram.cpp
    homography/main_test_homography.cpp
    integral/main_test_integral.cpp
    kalman/main_test_kalman.cpp
    klt_cycle/main_test_klt_cycle.cpp
    levenberg/main_test_levenberg.cpp
    logger/main_test_logger.cpp
    linear/main_test_linear.cpp
    matrix/main_test_matrix.cpp                        # TODO: Windows: assert at matrix\main_test_matrix.cpp:385 - Internal problem with double and stdout
    midmap_pyramid/main_test_midmap_pyramid.cpp
    moments/main_test_moments.cpp
    morphologic/main_test_morphologic.cpp
#    polynomDistortion/main_test_polynomDistortion.cpp  # TODO: check it...
    ransac/main_test_ransac.cpp
    readers/main_test_readers.cpp
    rectificator/main_test_rectificator.cpp
    rectificator1/main_test_rectificator1.cpp
    rgb24buffer/main_test_rgb24buffer.cpp
    rotation/main_test_rotation_lanzcos.cpp
    serializer/main_test_serializer.cpp
    similarity/main_test_similarity.cpp
    sphericdist/main_test_sphericdist.cpp
    ssewrappers/main_test_ssewrappers.cpp
    tbb_wrapper/main_test_tbb_wrapper.cpp
    triangulator/main_test_triangulator.cpp
    vector/main_test_vector.cpp
#    yuv/main_test_yuv.cpp
#    cameracalibration/main_test_camera_structs.cpp
    conic/main_test_conic.cpp
#    calstructs/main_test_calstructs.cpp
    polynomial/main_test_polynomial.cpp
    meshdraw/main_test_meshdraw.cpp
#    reconstruction/main_test_reconstruction.cpp
    meta/main_test_meta.cpp
    function/main_test_function.cpp
    deform/test_deform.cpp
    camerafixture/main_test_camerafixture.cpp
    renderer/main_test_renderer.cpp
    meshdraw/test_polymeshdraw.cpp
    raytrace/main_test_raytrace.cpp
    json/main_test_json.cpp
    utils/main_test_utils.cpp
    quadric/main_test_quadric.cpp
    planefit/main_test_planefit.cpp
    noise/main_test_noise.cpp
    projection/main_test_projection.cpp
    vptree/main_test_vptree.cpp
    meshfilter/main_test_meshfilter.cpp
    convexhull/main_test_convexhull.cpp
    wuRasterizer/main_test_wu_rasterizer.cpp
    bsptree/main_test_bsptree.cpp
    halfspace/main_test_halfspace.cpp
    orientedbox/main_test_orientedbox.cpp
    convexHull2d/main_test_convexHull2d.cpp
    processor6d/main_test_processor6d.cpp
    bezierRasterizer/main_test_bezier_rasterizer.cpp
    delaunay/main_test_delaunay.cpp
    bspRenderer/bspRenderTest.cpp
    bspRenderer/bspRenderer.cpp

    cppunit_test/MatcherTest.h
    snooker/commonTypes.h
    snooker/errors.h
    snooker/reflectionSegmentator.h
    snooker/snookerSegmentator.h
    stateMachineTest/test.h
    cppunit_test/MatcherTest.h
    snooker/commonTypes.h
    snooker/errors.h
    snooker/reflectionSegmentator.h
    snooker/snookerSegmentator.h
    stateMachineTest/test.h
    bspRenderer/bspRenderTest.h
    bspRenderer/bspRenderer.h
)

add_executable(${MODULE_NAME}_tests ${CORE_TEST_SOURCES})
target_link_libraries(${MODULE_NAME}_tests gtest_main ${MODULE_NAME})
