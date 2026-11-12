/**
 * LATENTRADAR TYPESCRIPT CLIENT
 * High-dimensional residual activation stream jailbreak detection client.
 */

export interface LatentAnalysisResult {
  verdict: 'SAFE' | 'JAILBREAK_DETECTED';
  cosineSimilarity: number;
  activationDriftScore: number;
  confidencePct: number;
  latencyMs: number;
  auditSha256: string;
}

export class LatentRadarClient {
  private readonly safetyThreshold: number;

  constructor(safetyThreshold: number = 0.75) {
    this.safetyThreshold = safetyThreshold;
  }

  public computeCosineSimilarity(vA: number[], vB: number[]): number {
    let dot = 0.0;
    let normA = 0.0;
    let normB = 0.0;
    for (let i = 0; i < vA.length; i++) {
      dot += vA[i] * vB[i];
      normA += vA[i] * vA[i];
      normB += vB[i] * vB[i];
    }
    const denom = Math.sqrt(normA) * Math.sqrt(normB);
    return denom === 0 ? 0 : dot / denom;
  }

  public evaluateDrift(cosineSim: number): 'SAFE' | 'JAILBREAK_DETECTED' {
    return cosineSim >= this.safetyThreshold ? 'SAFE' : 'JAILBREAK_DETECTED';
  }
}
