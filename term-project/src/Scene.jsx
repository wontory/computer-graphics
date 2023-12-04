import { OrbitControls } from '@react-three/drei';
import Car from './components/Car';
import Ball from './components/Ball';
import CrateBox from './components/CrateBox';
import Field from './components/Field';

function Scene() {
  return (
    <>
      <ambientLight intensity={0.5} />
      <directionalLight position={[-10, 10, 0]} intensity={0.4} />
      <OrbitControls />
      <Car />
      <Ball />
      <CrateBox />
      <Field />
    </>
  );
}

export default Scene;
