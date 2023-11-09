import { Suspense, useEffect, useState } from 'react';
import {
  Environment,
  OrbitControls,
  PerspectiveCamera,
} from '@react-three/drei';
import Track from './components/Track';
import Ground from './components/Ground';
import Car from './components/Car';

export default function Scene() {
  const [thirdPerson, setThirdPerson] = useState(false);
  const [cameraPosition, setCameraPosition] = useState([-6, 3.9, 6.21]);

  useEffect(() => {
    function keydownHandler(e) {
      if (e.key == 'k') {
        if (thirdPerson)
          setCameraPosition([-6, 3.9, 6.21 + Math.random() * 0.01]);
        setThirdPerson(!thirdPerson);
      }
    }

    window.addEventListener('keydown', keydownHandler);
    return () => window.removeEventListener('keydown', keydownHandler);
  });

  return (
    <Suspense fallback={null}>
      <Environment files="./textures/envmap.hdr" background="both" />

      <PerspectiveCamera makeDefault position={cameraPosition} fov={40} />
      {!thirdPerson && <OrbitControls target={[-2.64, -0.71, 0.03]} />}

      <Track />
      <Ground />
      <Car thirdPerson={thirdPerson} />
    </Suspense>
  );
}
