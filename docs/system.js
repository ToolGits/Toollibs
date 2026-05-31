async function checkSystemMode() {
  try {
    const res = await fetch("./maintenance.json", { cache: "no-store" });
    const data = await res.json();

    if (data.mode === "maintenance") {
      window.location.href = "maintenance.html";
      return;
    }

    if (data.mode === "degraded") {
      console.warn("Toollibs degraded mode:", data.reason);
    }

  } catch (e) {
    console.error("Failed to check system mode");
  }
}

window.onerror = function(message, source, lineno, colno, error) {
  console.error("Fatal error:", message);

  fetch("./maintenance.json", { cache: "no-store" })
    .then(r => r.json())
    .then(data => {
      if (data.mode !== "maintenance") {
        console.warn("System unstable detected");
      }
    });

  return false;
};

checkSystemMode();