import { useEffect, useRef } from 'react';
import { useFrame, useLoader } from '@react-three/fiber';
import { useBox, useRaycastVehicle } from '@react-three/cannon';
import { GLTFLoader } from 'three/examples/jsm/loaders/GLTFLoader';
import { WheelDebug } from './WheelDebug';
import { useWheels } from '../hooks/useWheel';
import { useControls } from '../hooks/useControls';
import { Vector3, Quaternion } from 'three';

export default function Car({ thirdPerson }) {
  const mesh = useLoader(GLTFLoader, './models/car.glb').scene;

  const position = [-1.5, 0.5, 3];
  const width = 0.15;
  const height = 0.07;
  const front = 0.15;
  const wheelRadius = 0.05;

  const chassisBodyArgs = [width, height, front * 2];
  const [chassisBody, chassisApi] = useBox(
    () => ({
      args: chassisBodyArgs,
      mass: 150,
      position,
    }),
    useRef(null)
  );

  const [wheels, wheelInfos] = useWheels(width, height, front, wheelRadius);

  const [vehicle, vehicleApi] = useRaycastVehicle(
    () => ({
      chassisBody,
      wheelInfos,
      wheels,
    }),
    useRef(null)
  );

  useControls(vehicleApi, chassisApi);

  useFrame((state) => {
    if (!thirdPerson) return;

    const position = new Vector3(0, 0, 0);
    position.setFromMatrixPosition(chassisBody.current.matrixWorld);

    const quaternion = new Quaternion(0, 0, 0, 0);
    quaternion.setFromRotationMatrix(chassisBody.current.matrixWorld);

    const wDir = new Vector3(0, 0, -1);
    wDir.applyQuaternion(quaternion);
    wDir.normalize();

    const cameraPosition = position
      .clone()
      .add(wDir.clone().multiplyScalar(-1).add(new Vector3(0, 0.3, 0)));

    state.camera.position.copy(cameraPosition);
    state.camera.lookAt(position);
  });

  useEffect(() => {
    mesh.scale.set(0.0012, 0.0012, 0.0012);
    mesh.children[0].position.set(-365, -18, -67);
  }, [mesh]);

  return (
    <group ref={vehicle} name="vehicle">
      <group ref={chassisBody} name="chassis">
        <primitive
          object={mesh}
          rotation-y={Math.PI}
          position={[0, -0.09, 0]}
        />
      </group>
      {/* <mesh ref={chassisBody}>
        <meshBasicMaterial transparent={true} opacity={0.3} />
        <boxGeometry args={chassisBodyArgs} />
      </mesh> */}
      {wheels.map((wheel, index) => (
        <WheelDebug
          key={`wheel-${index}`}
          wheelRef={wheel}
          radius={wheelRadius}
        />
      ))}
    </group>
  );
}
