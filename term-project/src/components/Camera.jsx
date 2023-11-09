import { useLayoutEffect, useRef } from 'react';
import { useFrame, useThree } from '@react-three/fiber';
import { OrbitControls } from '@react-three/drei';

function Camera() {
  const cameraRef = useRef(null);
  const controlsRef = useRef(null);
  const { gl, camera } = useThree();
  const set = useThree((state) => state.set);
  const size = useThree((state) => state.size);

  useLayoutEffect(() => {
    if (!cameraRef.current) return;
    cameraRef.current.aspect = size.width / size.height;
    cameraRef.current.updateProjectionMatrix();
  }, [size]);

  useLayoutEffect(() => {
    const camera = cameraRef.current;
    if (!camera) return;
    set(() => ({ camera }));
  }, []);

  useFrame(() => {
    if (!cameraRef.current || !controlsRef.current) return;
    cameraRef.current.updateMatrixWorld();
    controlsRef.current.update();
  });

  return (
    <>
      <perspectiveCamera ref={cameraRef} position={[0, -10, 10]} />
      <OrbitControls
        enableDamping
        ref={controlsRef}
        args={[camera, gl.domElement]}
        dampingFactor={0.2}
        minPolarAngle={Math.PI / 3}
        maxPolarAngle={Math.PI / 3}
      />
    </>
  );
}

export default Camera;
