import { Suspense, useMemo } from 'react';
import { Canvas } from '@react-three/fiber';
import { Physics } from '@react-three/rapier';
import { KeyboardControls } from '@react-three/drei';
import Scene from './Scene';

function App() {
  const map = useMemo(
    () => [
      { name: 'forward', keys: ['ArrowUp'] },
      { name: 'back', keys: ['ArrowDown'] },
      { name: 'left', keys: ['ArrowLeft'] },
      { name: 'right', keys: ['ArrowRight'] },
    ],
    []
  );

  return (
    <KeyboardControls map={map}>
      <Canvas shadows camera={{ position: [3, 3, 3], fov: 30 }}>
        <hemisphereLight intensity={0.75} />
        <ambientLight intensity={0.3} />
        <Suspense>
          <Physics>
            <Scene />
          </Physics>
        </Suspense>
      </Canvas>
    </KeyboardControls>
  );
}

export default App;
