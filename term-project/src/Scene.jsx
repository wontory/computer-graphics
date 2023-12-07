import { useRef, useState } from 'react';
import { Quaternion, Vector3 } from 'three';
import { useFrame, useThree } from '@react-three/fiber';
import { OrbitControls } from '@react-three/drei';
import { useBeforePhysicsStep } from '@react-three/rapier';
import { useControls } from './hooks/use-controls';
import Car from './components/Car/Car';
import Ball from './components/Ball';
import CrateBox from './components/CrateBox';
import Field from './components/Field';

const cameraIdealOffset = new Vector3();
const cameraIdealLookAt = new Vector3();
const chassisTranslation = new Vector3();
const chassisRotation = new Quaternion();

const Scene = () => {
  const [thirdPerson, setThirdPerson] = useState(false); // drive or orbit

  const raycastVehicle = useRef(null);

  const camera = useThree((state) => state.camera);
  const cameraPos = useRef(new Vector3(15, 15, 0));
  const cameraLookAt = useRef(new Vector3());

  const controls = useControls();

  useBeforePhysicsStep((world) => {
    if (raycastVehicle.current.rapierRaycastVehicle.current) {
      const {
        wheels,
        rapierRaycastVehicle: { current: vehicle },
        setBraking,
      } = raycastVehicle.current;

      let engineForce = 0;
      let steering = 0;
      const brakeForce = controls.current.brake;

      if (controls.current.forward) engineForce += 20;
      if (controls.current.backward) engineForce -= 20;
      if (controls.current.left) steering += 10;
      if (controls.current.right) steering -= 10;

      for (let i = 0; i < vehicle.wheels.length; i++)
        vehicle.setBrakeValue(brakeForce, i);

      vehicle.setSteeringValue(steering, 0);
      vehicle.setSteeringValue(steering, 1);
      vehicle.applyEngineForce(engineForce, 2);
      vehicle.applyEngineForce(engineForce, 3);

      vehicle.update(world.timestep);

      for (let i = 0; i < vehicle.wheels.length; i++) {
        const wheelObject = wheels[i].object.current;
        const wheelState = vehicle.wheels[i].state;
        wheelObject.position.copy(wheelState.worldTransform.position);
        wheelObject.quaternion.copy(wheelState.worldTransform.quaternion);
      }

      setBraking(brakeForce > 0);
    }
  });

  useFrame((_, delta) => {
    if (!thirdPerson) {
      const chassis = raycastVehicle.current?.chassisRigidBody;
      if (!chassis?.current) return;

      chassisRotation.copy(chassis.current.rotation());
      chassisTranslation.copy(chassis.current.translation());

      const t = 1.0 - Math.pow(0.01, delta);

      cameraIdealOffset.set(-10, 3, 0);
      cameraIdealOffset.applyQuaternion(chassisRotation);
      cameraIdealOffset.add(chassisTranslation);

      if (cameraIdealOffset.y < 0) cameraIdealOffset.y = 0.5;

      cameraIdealLookAt.set(0, 1, 0);
      cameraIdealLookAt.applyQuaternion(chassisRotation);
      cameraIdealLookAt.add(chassisTranslation);

      cameraPos.current.lerp(cameraIdealOffset, t);
      cameraLookAt.current.lerp(cameraIdealLookAt, t);

      camera.position.copy(cameraPos.current);
      camera.lookAt(cameraLookAt.current);
    }
  }, -51);

  return (
    <>
      <Car
        ref={raycastVehicle}
        position={[0, 5, 0]}
        rotation={[0, -Math.PI / 2, 0]}
      />
      <Ball position={[0, 0, 19]} />
      <CrateBox position={[0, 3, 30]} />
      <CrateBox position={[0, 4, 30]} />
      <CrateBox position={[0, 5, 30]} />
      <CrateBox position={[1, 3, 30]} />
      <CrateBox position={[1, 4, 30]} />
      <CrateBox position={[1, 5, 30]} />
      <CrateBox position={[-1, 3, 30]} />
      <CrateBox position={[-1, 4, 30]} />
      <CrateBox position={[-1, 5, 30]} />
      <Field />
      {thirdPerson && <OrbitControls />}
    </>
  );
};

export default Scene;
