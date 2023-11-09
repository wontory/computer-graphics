import { Suspense } from 'react';
import ReactDOM from 'react-dom/client';
import { Canvas } from '@react-three/fiber';
import { Physics } from '@react-three/cannon';
import Scene from './Scene.jsx';
import './index.css';

ReactDOM.createRoot(document.getElementById('root')).render(
  <Suspense fallback={'Loading'}>
    <Canvas>
      <Physics broadphase="SAP" gravity={[0, -5, 0]}>
        <Scene />
      </Physics>
    </Canvas>
  </Suspense>
);
